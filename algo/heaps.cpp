#include <algorithm>
#include <iostream>
#include <vector>


void printVector(const std::vector<int>& vec)
{
    for (const auto& item : vec)
        std::cout << item << " • ";
    std::cout << std::endl;
}

void printHeap(const std::vector<int>& vec)
{
    auto powerOfTwo = [&] (const int x)
    {
        return !(x == 0) && !(x & (x - 1));
    };

    int i = 1;
    for (const auto& item : vec)
        std::cout << item << (powerOfTwo(++i) ? " | " : " • ");
    std::cout << std::endl;
}

void print(const std::vector<int>& vec)
{
    if (std::is_heap(vec.begin(), vec.end()))
        printHeap(vec);
    else
        printVector(vec);
}


int main()
{
    /* START */
    std::vector<int> data { 3, 1, 4, 1, 5, 8, 2, 6, 5, 3, 5, 8, 9, 7, 9 };
    //std::vector<int> data { 9, 8, 7, 6, 6, 9, 5, 4, 4, 3, 3, 2, 2, 2, 1 };
    std::cout << std::endl << "original data...\n";
    print(data);

    // Force Heap
    if ( !std::is_heap(data.begin(), data.end()) )
    {
        std::cout << std::endl << "making heap...\n";
        std::make_heap(data.begin(), data.end());
        print(data);
    }

    /* NEW DATA */
    data.push_back(7);
    std::cout << std::endl << "New data...\n";
    print(data);

    // Force Heap
    if ( !std::is_heap(data.begin(), data.end()) )
    {
        std::cout << std::endl << "making heap...\n";
        std::make_heap(data.begin(), data.end());
        print(data);
    }

    /* REMOVE ROOT */
    std::cout << std::endl  << std::endl << "Remove head data\n";
    // pop heap - moves the largest to the end
    std::cout << "1) Copy to end...\n";
    std::pop_heap(data.begin(), data.end());
    print(data);

    // Remove largest/last element
    data.pop_back();
    print(data);

    // Force heap
    if ( !std::is_heap(data.begin(), data.end()) )
        std::make_heap(data.begin(), data.end());
    print(data);

    return 0;
}