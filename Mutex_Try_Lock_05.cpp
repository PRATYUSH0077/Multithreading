// 0. try lock() Tries to lock the mutex. Returns immediately. On successful lock acquisition returns true otherwise returns false.

// 1. If try lock() is not able to lock mutex, then it doesn't get blocked that's why it is called non-blocking and continue further execution like if else false condition in CP.

// 2. If try lock is called again by the same thread which owns the mutex, the behavior is undefined. It is a dead lock situation with undefined behaviour. (if you want to be able to lock the same autex by same thread More than one time the go for recursive mutex)
#include <iostream>
#include <thread>
#include <mutex>
using namespace std;
int counter = 0;
std::mutex mtx;
void increaseTheCounterFor100000Time()
{
    for (int i = 0; i < 100000; ++i)
    {
        if (mtx.try_lock())
        {
            ++counter;
            mtx.unlock();
        }
    }
}
int main()
{
    std::thread tl(increaseTheCounterFor100000Time);
    std::thread t2(increaseTheCounterFor100000Time);
    tl.join();
    t2.join();
    cout << "Counter: " << counter << endl;
    return 0;
}

/*
There are so many try lock function
1. std::tru_lock()
2. std::mutex::try lock
3.std::shared lock::try lock
4. std::timed mutex::try lock
5.std::unique lock::try_lock
6.std::shared mutex::try_lock
7.std::recursive mutex: try lock
8.std::shared timed mutex::try lock
9.std::recursive timed mutex: try lock
*/