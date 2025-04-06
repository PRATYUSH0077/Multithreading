/*
    few points to remember about timed mutex is as follows:
0. std::timed_mutex is blocked till timeout_time or the lock is acquired and returns true if success
   otherwise false.
1. Member Function:
   a. lock
   b. try_lock
   c. try_lock_for    ---\ These two functions makes it different from mutex.
   d. try_lock_until  ---/
   e. unlock

   EXAMPLE: try_lock_for();
    Waits until specified timeout_duration has elapsed or the lock is acquired, whichever comes first.
    On successful lock acquisition returns true, otherwise returns false.
*/

#include <iostream>
#include <thread>
#include <mutex>
#include <chrono>
using namespace std;
int myAmount = 0;
std::timed_mutex m;

// try_lock_for() mutex
void increment(int i)
{
    // if (m.try_lock_for(std::chrono::seconds(1)))
    if (m.try_lock_for(std::chrono::seconds(2)))
    {
        ++myAmount;
        // std::this_thread::sleep_for(std::chrono::seconds(2));
        std::this_thread::sleep_for(std::chrono::seconds(1));
        cout << "Thread" << i << " Entered" << endl;
        m.unlock();
    }
    else
    {
        cout << "Thread" << i << " Couldn't Enter" << endl;
    }
}
// try_lock_until() mutex

void increment2(int i)
{
    auto now = std::chrono::system_clock::now();
    // if (m.try_lock_for(std::chrono::seconds(1)))
    if (m.try_lock_until(now + std::chrono::seconds(2)))
    {
        ++myAmount;
        // std::this_thread::sleep_for(std::chrono::seconds(2));
        std::this_thread::sleep_for(std::chrono::seconds(1));
        cout << "Thread" << i << " Entered" << endl;
        m.unlock();
    }
    else
    {
        cout << "Thread" << i << " Couldn't Enter" << endl;
    }
}
int main()
{
    // try_lock_for() mutex
    std::thread t1(increment, 1);
    std::thread t2(increment, 2);
    t1.join();
    t2.join();

    // try_lock_until() mutex
    std::thread t3(increment, 1);
    std::thread t4(increment, 2);
    t3.join();
    t4.join();
    cout << myAmount << endl;
    return 0;
}