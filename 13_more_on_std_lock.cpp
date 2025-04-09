/*

std::lock() In C++11 It is used to lock multiple mutex at the same time.

syntax is as follow:
std::lock(m1, m2, m3, m4);
use case--> in condition where more than 1 mitex to be locked by different thread, to elimiate the deadlock situation

1. All arguments are locked via a sequence of calls to lock(),  try_lock(), or unlock() on each argument.
2. Order of locking is not defined (it will try to lock provided mutex in any order and ensure that there is no deadlock).
3. It is a blocking call.

[Example:0] -- No deadlock.
    Thread 1                    Thread 2
    std::lock(m1,m2);           std::lock(m1,m2);

[Example:1] -- No deadlock.

    Thread 1                    Thread 2
    std::lock(m1, m2);          std::lock(m2, m1);

[Example:2] -- No deadlock.

    Thread 1                    Thread 2
    std::lock(m1, m2, m3, m4);  std::lock(m3, m4);
                                std::lock(m1, m2);

[Example:3] -- Yes, the below can deadlock.

    Thread 1                    Thread 2
    std::lock(m1,m2);           std::lock(m3,m4);
    std::lock(m3,m4);           std::lock(m1,m2);

    bcz locking of mutex not under same lock , hence cannot unlock previosly locked mutex
*/

#include <iostream>
#include <thread>
#include <mutex>
using namespace std;
std::mutex m1;
std::mutex m2;
void thread1()
{
    while (1)
    {
        std::lock(m1, m2);
        cout << "Thread 1 " << endl;
        m1.unlock();
        m2.unlock();
    }
}
void thread2()
{
    while (1)
    {
        std::lock(m2, m1);
        cout << "Thread 2 " << endl;
        m1.unlock();
        m2.unlock();
    }
}
int main()
{
    thread tl(thread1);
    thread t2(thread2);
    tl.join();
    t2.join();

    // no deadlock situation arise
    return 0;
}