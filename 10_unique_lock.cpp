/*
Unique_lock In C++ programming language.

syntax ::  std::unique_lock<mutex> lock(m1)

Few important points to remember about the unique_lock:
1. The class unique_lock is a mutex ownership wrapper.
2. It Allows:
    a. Can Have Different Locking Strategies (See Locking Strategy below)
    b. time-constrained attempts at locking (try_lock_for, try_lock_until)
    syntax ::  std::unique_lock<mutex> lock.try_lock_for(m1,time_in sec)
    c. recursive locking
    d. transfer of lock ownership (move not copy)
    e. condition variables. (See this in coming videos)

Locking Strategies
    syntax ::  std::unique_lock<mutex> object1(m1,locking_strategy)
   TYPE         || EFFECTS(S)
1. defer_lock  ||  do not acquire ownership of the mutex.(not lock mutex but acquire onwership of mutex)
2. try_to_lock ||  try to acquire ownership of the mutex without blocking.
3. adopt_lock  ||  assume the calling thread already has ownership of the mutex.
                || used when an object already owning the mutex call a member func and that fucntion tries to lock the mutex again.
*/

#include <iostream>
#include <thread>
#include <mutex>
#include <chrono>
using namespace std;
int myAmount = 0;
std::mutex m;

// try_lock_for() mutex
void increment(string thread, int i)
{
    std::unique_lock<mutex> lock(m);
    for (int k = 0; k < i; k++)
    {
        myAmount++;
        cout << thread << " " << myAmount << endl;
    }
}
void increment2(string thread, int i)
{
    std::unique_lock<mutex> lock(m, std::defer_lock);
    // can have many lines of code here as the mutex m is still not locked.

    lock.lock();
    // no need to unlock as part of unique lock so destructor will take care of it.
    for (int k = 0; k < i; k++)
    {
        myAmount++;
        cout << thread << " " << myAmount << endl;
    }
}

int main()
{
    std::thread t1(increment, "T1", 1);
    std::thread t2(increment, "T2", 2);
    t1.join();
    t2.join();

    // deferred lock example
    std::thread t3(increment2, "T1", 1);
    std::thread t4(increment2, "T2", 2);
    t3.join();
    t4.join();

    return 0;
}