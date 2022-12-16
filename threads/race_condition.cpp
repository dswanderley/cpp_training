#include <iostream>
#include <thread>
#include <chrono>
#include <atomic>


using namespace std::chrono_literals;


std::atomic<double> g_value = {1.0};
std::atomic_bool g_running(true);


void function1()
{
    int counter = 0;
    while (g_running)
    {
        g_value = g_value/2.0 ;
        std::this_thread::sleep_for(100ms);
        counter++;
    }
    std::cout << "Function 1 ran " << counter << " times." << std::endl;
}


void function2()
{
    int counter = 0;
    while (g_running)
    {
        g_value = g_value*2.0;
        std::this_thread::sleep_for(100ms);
        counter++;
    }
    std::this_thread::sleep_for(10ms);
    std::cout << "Function 2 ran " << counter << " times." << std::endl;
}


int main()
{
    std::thread thread1, thread2, thread3;

    thread1 = std::thread(&function1);
    thread2 = std::thread(&function2);

    thread3 = std::thread([&]() {
        std::this_thread::sleep_for(2s);
        g_running = false;
    });

    thread1.join();
    thread2.join();
    thread3.join();

    std::cout << "Final value is: " << g_value << std::endl;

    return 0;
}