/*
    Producer Consumer OR Bounded Buffer Problem

THE PROBLEM STATEMENT:
 1. Producer will produce and consumer will consume with synchronisation of a common buffer.
 2. Until producer thread produces any data consumer thread can't consume.
 3. Threads will use condition_variable to notify each other.
 4. We need mutex if we use condition_variable because CV waits on mutex.
 5. This is one of the example of producer consumer there are many.

PRODUCER thread steps:
 1. lock mutex, if success then go ahead otherwise wait for mutex to get free.
 2. check if buffer is full and if it is full then unlock mutex and sleep, if not then go ahead and produce.
 3. insert item in buffer.
 4. unlock mutex.
 5. notify consumer.

CONSUMER thread steps:
 1. lock mutex, if success then go ahead otherwise wait for mutex to get free.
 2. check if buffer is empty and if it is, then unlock the mutex and sleep, if not then go ahead and consume.
 3. consume item from buffer.
 4. unlock mutex.
 5. notify producer.

IMP:
 Producer and Consumer have to notify each other upon completion of their job.


*/

#include <iostream>
#include <thread>
#include <chrono>
#include <mutex>
#include <condition_variable>
#include <deque>

using namespace std;

std::mutex CS;
std::condition_variable cond;
int MaxBufferSize = 5;
deque<int> buffer;

void Producer(int val)
{
    while (val)
    {
        std::unique_lock<std::mutex> locker(CS);
        cond.wait(locker, []()
                  { return buffer.size() < MaxBufferSize; });
        buffer.push_back(val);
        cout << "Producer produced : " << val << endl;
        val--;
        locker.unlock();
        cond.notify_one();
    }
}
void Consumer()
{
    while (true)
    {
        std::unique_lock<std::mutex> locker(CS);
        cond.wait(locker, []()
                  { return buffer.size() > 0; });
        int val = buffer.back();
        buffer.pop_back();
        cout << "Consumer consumed : " << val << endl;
        locker.unlock();
        cond.notify_one();
    }
}

int main()
{
    std::thread t1(Producer, 10);
    std::thread t2(Consumer);
    t1.join();
    t2.join();
    return 0;
}
