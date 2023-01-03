#ifndef ALGO_H
#define ALGO_H

#include <algorithm>
#include <iostream>


namespace algo {

    template<class Iter>
    void mergeSort(Iter first, Iter last)
    {
        if (last - first > 1)
        {
            Iter middle = first + (last - first) / 2;
            mergeSort(first, middle);
            mergeSort(middle, last);
            std::inplace_merge(first, middle, last);
        }
    };


    static void printVector(const std::vector<int>& vec)
    {
        for (const auto& item : vec)
            std::cout << item << " | ";
        std::cout << std::endl;
    }

}


#endif // ALGO_H