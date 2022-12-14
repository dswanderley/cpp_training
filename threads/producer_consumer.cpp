#include <iostream>
#include <vector>
#include <thread>
#include <chrono>
#include <mutex>
#include <condition_variable>
#include <atomic>

#define MAX_SIZE 1000000

using namespace std::chrono_literals;


void fnSource1(std::vector<int>* const vector, std::mutex& mtx, std::condition_variable& cond)
{
    while (vector->size() < MAX_SIZE)
    {
        // Lock mutex
        std::unique_lock<std::mutex> lock(mtx);
        // Update vector
        vector->push_back(1);
        // Unlock mutex
        lock.unlock();
        // Notify all threads
        cond.notify_all();
        // Wait
        std::this_thread::sleep_for(2ms);
    }
}


void fnSource2(std::vector<int>* const vector, std::mutex& mtx, std::condition_variable& cond)
{
    while (vector->size() < MAX_SIZE)
    {
        // Lock mutex inside this scope
        {
            std::unique_lock<std::mutex> lock(mtx);
            vector->push_back(2);
        }
        // Notify all threads
        cond.notify_all();
        // Wait
        std::this_thread::sleep_for(2ms);
    }
}

void fnReader(std::vector<int>* const vector, std::mutex& mtx, std::condition_variable& cond, const std::atomic_bool& runing)
{
    while (runing)
    {
        // Lock mutex inside this scope
        {
            std::unique_lock<std::mutex> lock(mtx);
            if (!vector->empty())
            {
                const int i = vector->back();
                vector->pop_back();

                std::cout << i << std::endl;
            }
            // Wait for new elements
            cond.wait(lock);
        }
    }
}


int main()
{
    // Start variables
    std::thread thread1, thread2, thread3;
    std::atomic_bool runing{true};
    std::mutex mtx;
    std::condition_variable cond;
    std::vector<int>* vector = new std::vector<int>();                // Target vector

    thread3 = std::thread(&fnReader,  vector, std::ref(mtx), std::ref(cond), std::ref(runing));
    thread1 = std::thread(&fnSource1, vector, std::ref(mtx), std::ref(cond));
    thread2 = std::thread(&fnSource2, vector, std::ref(mtx), std::ref(cond));

    // Wait vector filling
    std::this_thread::sleep_for(2s);
    runing = false;

    // Conclude threads
    thread3.join();
    thread1.detach();
    thread2.detach();

    std::cout << "Vector size: " <<  vector->size() << std::endl;

    delete vector;

    return 0;
}