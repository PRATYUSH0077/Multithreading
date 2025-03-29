#include <iostream>
#include <thread>
#include <chrono>
#include <algorithm>
using namespace std;
using namespace std::chrono;

void run(int x)
{
    // std::this_thread::sleep_for(chrono::seconds(5));
    while (x-- > 0)
    {
        cout << "HI" << endl;
    }
    std::this_thread::sleep_for(chrono::seconds(5));
}

// JOIN FUNCTION

// int main()
// {
//     std::thread t1(run, 4);
//     // the main function pointer will point here  after just calling t1 and not waiting for it to complete unless joion() is called.
//     cout << "before join" << endl;
//     if (t1.joinable())
//         t1.join();
//     // t1.join(); // will result in runtime system error due to more than one instance of calling joijn on same thread , no syntactical or syntax error
//     cout << "after join" << endl;
// }

// DETACH FUNCTION

int main()
{
    std::thread t1(run, 4);
    cout << "before join" << endl;
    t1.detach(); // Detached from parent node hence both functio independently. However if parent node execution over before OS can start execution of thread then t1 will not be implemented.
    // Also no synchronization of implementation of parent and child like O/P like this:
    /*
        before join
        HI
        HIafter join
        HI

        HI
     */
    if (t1.joinable())
        t1.detach(); // double detach again problem
    cout << "after join" << endl;
}

// Always use join() or detach() as thread destructor check if thread joinable and if yes, terminate the program hence thread terminated at the time of creation only.