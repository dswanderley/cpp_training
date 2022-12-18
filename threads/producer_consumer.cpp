#include <iostream>
#include <vector>
#include <thread>
#include <chrono>
#include <mutex>
#include <condition_variable>
#include <atomic>

#define MAX_SIZE 1000000

using namespace std::chrono_literals;


std::atomic_bool runing{true};
std::mutex g_mtx;
std::vector<int> g_vector;
std::condition_variable g_cond;


void fnSource1()
{
    while (g_vector.size() < MAX_SIZE)
    {
        // Lock mutex
        std::unique_lock<std::mutex> lock(g_mtx);
        // Update vector
        g_vector.push_back(1);
        // Unlock mutex
        lock.unlock();
        // Notify all threads
        g_cond.notify_all();
        // Wait
        std::this_thread::sleep_for(2ms);
    }
}


void fnSource2()
{
    while (g_vector.size() < MAX_SIZE)
    {
        // Lock mutex inside this scope
        {
            std::unique_lock<std::mutex> lock(g_mtx);
            g_vector.push_back(2);
        }
        // Notify all threads
        g_cond.notify_all();
        // Wait
        std::this_thread::sleep_for(2ms);
    }
}

void fnReader()
{
    while (runing)
    {
        // Lock mutex inside this scope
        {
            std::unique_lock<std::mutex> lock(g_mtx);
            if (!g_vector.empty())
            {
                const int i = g_vector.back();
                g_vector.pop_back();

                std::cout << i << std::endl;
            }
            // Wait for new elements
            g_cond.wait(lock);
        }
    }
}


int main()
{
    std::thread thread1, thread2, thread3;

    thread3 = std::thread(&fnReader);
    thread1 = std::thread(&fnSource1);
    thread2 = std::thread(&fnSource2);


    std::this_thread::sleep_for(2s);
    runing = false;

    thread3.join();
    thread1.detach();
    thread2.detach();

    std::cout << "Vector size: " <<  g_vector.size() << std::endl;

    return 0;
}