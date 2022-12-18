#include <iostream>
#include <vector>
#include <thread>
#include <chrono>
#include <mutex>
#include <condition_variable>

#define MAX_SIZE 1000

using namespace std::chrono_literals;


std::mutex g_mtx;
std::vector<int> g_vector;


void fnSource1()
{
    while (g_vector.size() < MAX_SIZE)
    {
        //g_mtx.lock();
        {
            std::lock_guard<std::mutex> lock(g_mtx);
            g_vector.push_back(1);
        }
        //g_mtx.unlock();
        std::this_thread::sleep_for(1ms);
    }
}


void fnSource2()
{
    while (g_vector.size() < MAX_SIZE)
    {
        {
            std::unique_lock<std::mutex> lock(g_mtx);
            g_vector.push_back(2);
        }
        std::this_thread::sleep_for(1ms);
    }
}



int main()
{
    std::thread thread1, thread2;

    thread1 = std::thread(&fnSource1);
    thread2 = std::thread(&fnSource2);

    thread1.join();
    thread2.join();

    int c1, c2 = 0;

    for (int i = 0; i < g_vector.size(); i++)
    {
        if (g_vector[i] == 2)
            c2++;
        else if (g_vector[i] == 1)
            c1++;
        else
            std::cout << "Error at index " << i << std::endl;
    }

    std::cout << "Vector size: " <<  g_vector.size() << std::endl;
    std::cout << "Counter 1: " <<  c1 << std::endl;
    std::cout << "Counter 2: " <<  c2 << std::endl;

    return 0;
}