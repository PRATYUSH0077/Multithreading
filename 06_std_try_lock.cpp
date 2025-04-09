#include <chrono>
#include <functional>
#include <iostream>
#include <mutex>
#include <thread>
#include <vector>
using namespace std;
/*
    std::try_lock() In C++11 Threading
    1. std::try_lock() tries to lock all the lockable objects passed in it one by one in given  order.
    SYNTAX: std::try_lock(m1, m2,m3,m4...,mn);
    2. On success this function returns -1 otherwise it will return 0-based mutex index number  which it could not lock.
    3. If it fails to lock any of the mutex then it will release all the mutex it locked before.
    4. If a call to try_lock results in an exception, unlock is called for any locked objects   before rethrowing.
*/
int foo_count = 0;
int bar_count = 0;
int overall_count = 0;
bool done = false;
std::mutex foo_count_mutex;
std::mutex bar_count_mutex;
std::mutex done_mutex;
void increment(int &counter, std::mutex &m, const char *desc)
{
    for (int i = 0; i < 10; ++i)
    {
        m.lock();
        ++counter;
        std::cout << desc << ": " << counter << '\n';
        m.unlock();
        std::this_thread::sleep_for(std::chrono::seconds(1));
    }
};

void Join()
{
    done_mutex.lock();
    while (!done)
    {
        done_mutex.unlock();
        int result = std::try_lock(foo_count_mutex, bar_count_mutex);
        // if -1 then all lock successful
        if (result == -1)
        {
            overall_count += foo_count + bar_count;
            foo_count = 0;
            bar_count = 0;
            std::cout << "overall: " << overall_count << '\n';
            foo_count_mutex.unlock();
            bar_count_mutex.unlock();
        }
        std::this_thread::sleep_for(std::chrono::seconds(2));
        done_mutex.lock();
    }
    done_mutex.unlock();
}
int main()
{
    std::thread increment_foo(increment, std::ref(foo_count), std::ref(foo_count_mutex), "foo");
    std::thread increment_bar(increment, std::ref(bar_count), std::ref(bar_count_mutex), "bar");
    std::thread update_overall(Join);

    increment_foo.join();
    increment_bar.join();
    // done_mutex.lock();
    done = true;
    // done_mutex.unlock();
    update_overall.join();

    std::cout << "Done processing\n"
              << "foo: " << foo_count << '\n'
              << "bar: " << bar_count << '\n'
              << "overall: " << overall_count << '\n';
}