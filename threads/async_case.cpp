#include <iostream>
#include <vector>
#include <chrono>
#include <thread>
#include <mutex>
#include <future>


using namespace std::chrono_literals;
using namespace std::chrono;            // high_resolution_clock & milliseconds


int function1()
{
    // Mesure time
    auto start = high_resolution_clock::now();
    // Run function / sleep
    std::this_thread::sleep_for(50ms);
    // Get stop time
    auto stop = high_resolution_clock::now();
    // Compute duration
    auto duration = duration_cast<milliseconds>(stop - start);
    std::cout << "function1 ran in : " << duration.count() << "ms." << std::endl;

    return 1;
}


int function2()
{
    // Mesure time
    auto start = high_resolution_clock::now();
    // Run function / sleep
    std::this_thread::sleep_for(100ms);
    // Get stop time
    auto stop = high_resolution_clock::now();
    // Compute duration
    auto duration = duration_cast<milliseconds>(stop - start);
    std::cout << "function2 ran in : " << duration.count() << "ms." << std::endl;

    return 2;
}


int main()
{

    // Define functions
    std::future<int> fcn1, fcn2;
    fcn1 = std::async(&function1);
    fcn2 = std::async(&function2);

    // Mesure time
    auto start = high_resolution_clock::now();

    // Run functions
    int res2 = fcn2.get();
    int res1 = fcn1.get();

    int res = res1 + res2;

    // Get stop time
    auto stop = high_resolution_clock::now();
    auto duration = duration_cast<milliseconds>(stop - start);

    // Show results
    std::cout << "Total time is: " << duration.count() << "ms" << std::endl;
    std::cout << "Result is: " << res << std::endl;

    return 0;
}