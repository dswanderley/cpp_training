#include <iostream>
#include <thread>
#include <chrono>


using namespace std::chrono_literals;


void function1()
{
    std::this_thread::sleep_for(500ms);
    while (true)
    {
        std::cout << "Function 1" << std::endl;
        std::this_thread::sleep_for(101ms);
    }
};


void function2(int start, int end)
{
    std::this_thread::sleep_for(500ms);
    for (int i = start; i < end+1; i++)
    {
        std::this_thread::sleep_for(200ms);
        std::cout << "Function 2 (" << i << ")" << std::endl;
    }
};


void function3(bool* flag)
{
    std::this_thread::sleep_for(500ms);
    *flag = false;
};


int main()
{

    bool flag = true;
    int start = 10;
    int end = 100;

    std::thread thread1, thread2, thread3;

    std::cout << std::boolalpha << "Before starting, thread 1 joinable: " << thread1.joinable() << std::endl;
    std::cout << std::boolalpha << "Before starting, thread 2 joinable: " << thread2.joinable() << std::endl;

    // Start thread 1
    thread1 = std::thread(&function1);
    std::cout << std::boolalpha << "After  starting, thread 1 joinable: " << thread1.joinable() << std::endl;

    // Start thread 2
    thread2 = std::thread(&function2, start, end);
    std::cout << std::boolalpha << "After  starting, thread 2 joinable: " << thread2.joinable() << std::endl;

    // Start thread 3
    thread3 = std::thread(&function3, &flag);

    while (flag)
    {
        std::this_thread::sleep_for(1ms);
    }

    // Complete threads
    thread3.join();
    thread2.join();         // Wait for ending
    thread1.detach();       // Stop immediately

    std::cout << std::boolalpha << "After  detach, thread 1 joinable: " << thread1.joinable() << std::endl;
    std::cout << std::boolalpha << "After  join,   thread 2 joinable: " << thread2.joinable() << std::endl;

    return 0;
}