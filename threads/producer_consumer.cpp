#include <iostream>
#include <vector>
#include <thread>
#include <chrono>
#include <condition_variable>
#include <atomic>

using namespace std::chrono_literals;


std::atomic_bool runing{true};
std::mutex g_mtx;
std::vector<int> g_vector;


void fnSource1()
{
    while (g_vector.size() < 1000000)
    {
        //g_mtx.lock();
        {
            std::unique_lock<std::mutex> lock(g_mtx);
            g_vector.push_back(1);
        }
        //g_mtx.unlock();
        //std::this_thread::sleep_for(50ms);
    }
}


void fnSource2()
{
    while (g_vector.size() < 1000000)
    {
        {
            std::unique_lock<std::mutex> lock(g_mtx);
            g_vector.push_back(2);
        }
        //std::this_thread::sleep_for(50ms);
    }
}

void fnReader()
{
    int i = 0;
    //std::this_thread::sleep_for(1s);

    while (runing)
    {
        if (!g_vector.empty())
        {
            std::unique_lock<std::mutex> lock(g_mtx);
            i = g_vector.back();
            g_vector.pop_back();

            std::cout << i << std::endl;
        }
        //std::this_thread::sleep_for(10ms);
    }
}


int main()
{
    std::thread thread1, thread2, thread3;

    thread1 = std::thread(&fnSource1);
    thread2 = std::thread(&fnSource2);

    thread3 = std::thread(&fnReader);

    std::this_thread::sleep_for(1s);
    runing = false;

    thread3.join();
    thread1.detach();
    thread2.detach();

    return 0;
}