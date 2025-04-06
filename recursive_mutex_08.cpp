/*
recursive Mutex is very helpful when we have to put lock in recursive function calls.

Few points to remember:
0. It is same as mutex but, Same thread can lock one mutex multiple times using recursive_mutex.
1. If thread T1 first call lock/try_lock on recursive mutex m1, then m1 is locked by T1, now
   as T1 is running in recursion T1 can call lock/try_lock any number of times there is no issue.
2. But if T1 have acquired 10 times lock/try_lock on mutex m1 then thread T1 will have to unlock
   it 10 times otherwise no other thread will be able to lock mutex m1.
   It means recursive_mutex keeps count how many times it was locked so that many times it should be unlocked.
3. How many time we can lock recursive_mutex is not defined but when system stack limit  reaches and if we were calling
   lock() it will return std::system_error OR if we were calling try_lock() then it will return false.

Final INTERVIEW point of view:
0. It is similar to mutex but have extra facility that it can be locked multiple time by same thread.
1. If we can avoid recursive_mutex then we should because it brings overhead to the system.
2. It can be used in loops also.
*/

#include <iostream>
#include <thread>
#include <mutex>
#include <chrono>
using namespace std;

std::recursive_mutex m;
int global = 0;
void recursion(char c, int limit)
{
    if (limit <= 0)
    {
        return;
    }
    m.lock();
    cout << "Thread ID: " << c << " " << global << endl;
    global++;
    recursion(c, limit - 1);
    m.unlock();
    cout << "Unlocked by Thread: " << c << endl;
}

int main()
{
    std::thread t1(recursion, 'a', 3);
    std::thread t2(recursion, 'b', 3);
    t1.join();
    t2.join();
    return 0;
}