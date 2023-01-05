
#include <ctime>
#include <vector>
#include "algo.hpp"
#include "rdtsc.h"


int main()
{
    const int maxVal = 100;
    const int length = 50000;
    int64_t t0, tf;

    std::vector<int> data(length);

    srand(time(NULL));

    std::generate(  data.begin(),
                    data.end(),
                    [&]() -> int { return std::rand() % maxVal; }
                 );

    std::cout << "\nUnsorted array" << std::endl;
    //algo::printVector(data);
    std::cout << std::endl;

    /**
     * Bubble sort
     */
    std::cout << "Bubble Sort" << std::endl;
    {
        // Copy vector
        std::vector<int> sdata(data);
        // Sorting
        t0 = rdtsc();
        algo::bubbleSort(sdata.begin(), sdata.end());
        tf = rdtsc();
        // Print result
        //algo::printVector(sdata);
        printrRDTSC(t0, tf);
    }
    std::cout << std::endl;

    /**
     * Insertion sort
     */
    std::cout << "Insertion Sort" << std::endl;
    {
        // Copy vector
        std::vector<int> sdata(data);
        // Sorting
        t0 = rdtsc();
        algo::insertionSort(sdata.begin(), sdata.end());
        tf = rdtsc();
        // Print result
        //algo::printVector(sdata);
        printrRDTSC(t0, tf);
    }
    std::cout << std::endl;

    /**
     * Selection Sort
    */
    std::cout << "Selection Sort" << std::endl;
    {
        // Copy vector
        std::vector<int> sdata(data);
        // Sorting
        t0 = rdtsc();
        algo::selectionSort(sdata.begin(), sdata.end());
        tf = rdtsc();
        // Print result
        //algo::printVector(sdata);
        printrRDTSC(t0, tf);
    }
    std::cout << std::endl;

    /**
     * Quick sort
     */
    std::cout << "Quick Sort" << std::endl;
    {
        // Copy vector
        std::vector<int> sdata(data);
        // Sorting
        t0 = rdtsc();
        algo::quickSort(sdata.begin(), sdata.end());
        tf = rdtsc();
        // Print result
        //algo::printVector(sdata);
        printrRDTSC(t0, tf);
    }
    std::cout << std::endl;

    /**
     * Merge sort
     */
    std::cout << "Merge Sort" << std::endl;
    {
        // Copy vector
        std::vector<int> sdata(data);
        // Sorting
        t0 = rdtsc();
        algo::mergeSort(sdata.begin(), sdata.end());
        tf = rdtsc();
        // Print result
        //algo::printVector(sdata);
        printrRDTSC(t0, tf);
    }
    std::cout << std::endl;

    return 0;
}