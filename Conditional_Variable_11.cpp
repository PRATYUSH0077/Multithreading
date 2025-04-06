/*
    n this video we will learn how to use "Condition Variable In C++ Threading".
Few important points to remember while using "condition variables" are as follows:
1. Condition variables allow us to synchronise threads via notifications.
   a. notify_one();
   b. notify_all();
2. You need mutex to use condition variable
3. Condition variable is used to synchronise two or more threads.
4. Best use case of condition variable is Producer/Consumer problem.
5. Condition variables can be used for two purposes:
    a. Notify other threads
    b. Wait for some condition



std::condition_variable::wait can be called with a predicate (a callable object such as a function or lambda), and it will repeatedly check that the predicate returns true. If the predicate returns false, the thread will continue waiting.

Where predicate is a callable that takes no parameters and returns a bool.
*/

#include <iostream>
#include <thread>
#include <mutex>
#include <condition_variable>
using namespace std;
std::condition_variable cv;
std::mutex m;
long balance = 0;
void addMoney(int money)
{
    cout << "addmoney called" << endl;

    std::lock_guard<mutex> lg(m);
    balance += money;
    cout << "Amount Added Current Balance: " << balance << endl;
    cv.notify_one();
}
bool checkBalance(int money)
{
    return (money != 0);
}
void withdrowMoney(int money)
{
    cout << "withdrowMoney called here but waiting till balance update from condition variable" << endl;
    std::unique_lock<mutex> ul(m);
    cv.wait(ul, [&]()
            { return checkBalance(money); });

    if (balance >= money)
    {
        balance -= money;
        cout << "Amount Deducted: " << money << endl;
    }
    else
    {
        cout << "Amount Can't Be Deducted, Current Balance Is Less Than " << money << endl;
    }
    cout << "Current Balance Is: " << balance << endl;
}
int main()
{
    std::thread tl(withdrowMoney, 500);
    std::thread t2(addMoney, 500);
    tl.join();
    t2.join();
    return 0;
}