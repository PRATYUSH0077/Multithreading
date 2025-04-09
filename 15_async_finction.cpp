/*
    Runs a fucntion asyncgronusly and returns  a std::future that will hold the result

    There are three different launch policy for creating task using std::async are as follows:
    1. std::launch::async
    -> create thread then and there , seperate from main thread
    2. std::launch::deffered
    -> call the thread object when future object is called, runs in the same thread as that of main
    3. std::launch::async | std::launch::deffered
    -> let processor decide what to use.

    With the help of above policies std::async decides to create task as asynchronous or synchronous.
*/

#include <bits/stdc++.h>
#include <thread>
typedef long int ull;
using namespace std;

ull findOdd(ull start, ull end)
{
    ull OddSum = 0;
    for (ull i = start; i <= end; ++i)
    {
        if (i & 1)
        {
            OddSum += i;
        }
    }

    return OddSum;
}
int main()
{

    // ull start = 0, end = 1900;
    ull start = 0, end = 190000000;

    auto begin = std::chrono::steady_clock::now();
    std::future<ull> OddSum = std::async(std::launch::async, findOdd, start, end);
    cout << "OddSum : " << OddSum.get() << endl;
    auto finish = std::chrono::steady_clock::now();

    auto begin2 = std::chrono::steady_clock::now();
    std::future<ull> OddSum2 = std::async(std::launch::deferred, findOdd, start, end);
    cout << "OddSum : " << OddSum2.get() << endl;
    auto finish2 = std::chrono::steady_clock::now();

    std::cout << "Time difference async= " << std::chrono::duration_cast<std::chrono::microseconds>(finish - begin).count() << " " << std::endl;
    std::cout << "Time difference deferred = " << std::chrono::duration_cast<std::chrono::microseconds>(finish2 - begin2).count() << " " << std::endl;
    return 0;
}