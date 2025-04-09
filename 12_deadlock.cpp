#include <iostream>
#include <thread>
#include <mutex>
using namespace std;
std::mutex m1;
std::mutex m2;
void thread1()
{
    m1.lock();
    cout << "T1 acquired m1 \n";
    std::this_thread::sleep_for(2000ms);
    m2.lock();
    cout << "T1 acquired m2  \n";
    cout << "Critical Section Of Thread Thread One\n";
    m1.unlock();
    m2.unlock();
}
void thread2()
{
    m2.lock();
    cout << "T2 acquired m2 \n";
    std::this_thread::sleep_for(2000ms);
    m1.lock();
    cout << "T2 acquired m1 \n";
    cout << "Critical Section Of Thread Thread Two\n";
    m2.unlock();
    m1.unlock();
}
int main()
{
    thread tl(thread1);
    thread t2(thread2);
    tl.join();
    t2.join();
    return 0;
}