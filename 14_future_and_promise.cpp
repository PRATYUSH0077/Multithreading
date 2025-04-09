/*
std::promise and std::future and how they work together to synchronise threads.

-> Basically std::promise is sent to the called thread and once the value is ready we set that value in promise object
->  now at calling thread side we get that value using std::future object which was created using std::promise object before sending it to the called thread. And this is how we receive value from one thread to another in synchronisation.

*/
#include <bits/stdc++.h>
#include <thread>
typedef long int ull;
using namespace std;

void findOdd(std::promise<ull> &&OddSumPromise, ull start, ull end)
{
    ull OddSum = 0;
    for (ull i = start; i <= end; ++i)
    {
        if (i & 1)
        {
            OddSum += i;
        }
    }
    // std::this_thread::sleep_for(2s);
    OddSumPromise.set_value(OddSum);
}
int main()
{

    ull start = 0, end = 1900;
    // ull start = 0, end = 190000000;

    std::promise<ull> OddSum;
    std::future<ull> Odd_Future = OddSum.get_future();
    // created future object upon which the value will be called in future

    std::thread t1(findOdd, std::move(OddSum), start, end);
    cout << "Waiting For Result!!" << endl;
    cout << "OddSum: " << Odd_Future.get() << endl;
    // if value of promise object is set, immediately fetch it
    // otherwise wait for the value to be calculated

    cout << "Waiting For Result2!!" << endl;
    cout << "Completed!!" << endl;

    t1.join();
    return 0;
}