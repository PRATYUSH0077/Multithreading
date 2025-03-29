#include <iostream>
#include <thread>
#include <chrono>
#include <algorithm>
using namespace std;
using namespace std::chrono;
typedef long long int ull;

/*example
    1. word spell checker simultaneous check
*/

/*
    ways to make thread:
        1. function pointer -> thread create, pass function, then all parameter related to function
*/

void findEven(ull start, ull end, ull *EvenSum)
{
    for (ull i = start; i <= end; ++i)
    {
        if (!(i & 1))
        {
            *(EvenSum) += i;
        }
    }
}

void findOdd(ull start, ull end, ull *OddSum)
{
    for (ull i = start; i <= end; ++i)
    {
        if (i & 1)
        {
            (*OddSum) += i;
        }
    }
}

int main()
{

    ull start = 0, end = 1900000000;

    ull OddSum = 0;
    ull EvenSum = 0;

    // ------function pointer type thread------
    //  WITH THREAD
    auto startTime = high_resolution_clock::now();
    std::thread t1(findEven, start, end, &(EvenSum));
    std::thread t2(findOdd, start, end, &(OddSum));
    t1.join();
    t2.join();
    auto stopTime = high_resolution_clock::now();
    auto duration = duration_cast<microseconds>(stopTime - startTime);

    // WITHOUT THREAD
    auto startTime2 = high_resolution_clock::now();
    findEven(start, end, &EvenSum);
    findOdd(start, end, &OddSum);
    auto stopTime2 = high_resolution_clock::now();
    auto duration2 = duration_cast<microseconds>(stopTime2 - startTime2);

    cout << "OddSum : " << OddSum << endl;
    cout << "EvenSum : " << EvenSum << endl;

    cout << "With Thread Sec: " << duration.count() / 1000000 << endl;
    cout << "Without Thread Sec: " << duration2.count() / 1000000 << endl;

    return 0;
}