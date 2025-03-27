#include <iostream>
#include <thread>
#include <chrono>
#include <algorithm>
using namespace std;
using namespace std::chrono;
typedef long long int ull;

void fun(int x)
{
    cout << x << endl;
}

int main()
{
    // 1. function thread
    std::thread t1(fun, 10);
    t1.join();

    // 2. lamda function thread
    auto fun2 = [](int x)
    {
        cout << x << endl;
    };
    std::thread t2(fun, 12);
    std::thread t3([](int x)
                   { cout << x << endl; }, 15);
    t2.join();
    t3.join();

    class Base
    {
    public:
        void display(int x)
        {
            cout << x << endl;
        }
        static void display2(int x)
        {
            cout << x << endl;
        }
    };

    // 3. Non static Member Function
    Base b;
    std::thread t4(&Base::display, &b, 20);
    t4.join();

    // 4. static Member Function
    std::thread t5(&Base::display2, 30); // no need to pass object
    t5.join();
    return 0;
}