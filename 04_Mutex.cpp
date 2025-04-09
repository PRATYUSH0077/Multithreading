// Mutex In C++ Threading | Why Use Mutex | What Is Race Condition And How To Solve It ? | What Is Critical Section

// Mutex: Mutual Exclusion

// RACE CONDITION:
// 0.  Race condition is a situation where two or more threads  process happend to change a common data at the same time.
// 1. If there is a race condition then we have to protect it and the protected setion is called critical section/region.

// MUTEX:
// 0. Mutex is used to avoid race condition.
// 1. We use lock(), unlock() on mutex to avoid race condition.

#include <iostream>
#include <thread>
#include <mutex>
using namespace std;
int myAmount = 0;
std::mutex m;
void addMoney()
{
    m.lock();
    ++myAmount;
    m.unlock();
}

/*
    the thread which cannot acquire , that thread's execution is blocked at that point of time only, and unless that mutex is unlocked that thread waits at that point.
    Mutex-> like lock of door for a single room(CPU).
*/
int main()
{
    std::thread tl(addMoney);
    std::thread t2(addMoney);
    tl.join();
    t2.join();
    cout << myAmount << endl;
    return 0;
}