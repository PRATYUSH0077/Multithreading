/*

points to remember about the lock_guard :
0. It is very light weight wrapper for owning mutex on scoped basis.
(function scope over -> then unlock automatically)
1. It acquires mutex lock the moment you create the object of lock_guard.
2. It automatically removes the lock while goes out of scope.
3. You can not explicitly unlock the lock_guard.
(destructor of lock_guard automatically unlock the mutex object)
4. You can not copy lock_guard.


Use-Case:
    To be used when want the user to know i want my mutex to be unlocked only when scope of fucntion is over.
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
    std::lock_guard<mutex> lock(m);
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

    return 0;
}