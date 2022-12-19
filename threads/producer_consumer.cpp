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
std::condition_variable g_cond;


void fnSource1(std::vector<int>& vector)
{
    while (vector.size() < MAX_SIZE)
    {
        // Lock mutex
        std::unique_lock<std::mutex> lock(g_mtx);
        // Update vector
        vector.push_back(1);
        // Unlock mutex
        lock.unlock();
        // Notify all threads
        g_cond.notify_all();
        // Wait
        std::this_thread::sleep_for(2ms);
    }
}


void fnSource2(std::vector<int>& vector)
{
    while (vector.size() < MAX_SIZE)
    {
        // Lock mutex inside this scope
        {
            std::unique_lock<std::mutex> lock(g_mtx);
            vector.push_back(2);
        }
        // Notify all threads
        g_cond.notify_all();
        // Wait
        std::this_thread::sleep_for(2ms);
    }
}

void fnReader(std::vector<int>& vector)
{
    while (runing)
    {
        // Lock mutex inside this scope
        {
            std::unique_lock<std::mutex> lock(g_mtx);
            if (!vector.empty())
            {
                const int i = vector.back();
                vector.pop_back();

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


    std::vector<int> vector;

    thread3 = std::thread(&fnReader, std::ref(vector));
    thread1 = std::thread(&fnSource1, std::ref(vector));
    thread2 = std::thread(&fnSource2, std::ref(vector));


    std::this_thread::sleep_for(2s);
    runing = false;

    thread3.join();
    thread1.detach();
    thread2.detach();

    std::cout << "Vector size: " <<  vector.size() << std::endl;

    return 0;
}