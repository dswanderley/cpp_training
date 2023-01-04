#ifndef ALGO_H
#define ALGO_H

#include <algorithm>
#include <iostream>


namespace algo {

    /**
     * @brief Merge sort algorithm.
     *
     * @tparam Iter Vector iterator
     * @param first First vector index to be sorted
     * @param last Last vector index to be sorted
     */
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

    /**
     * @brief  Bubble Sort algorithm.
     *
     * @tparam Iter Vector iterator
     * @param first First vector index to be sorted
     * @param last Last vector index to be sorted
     */
    template<class Iter>
    void bubbleSort(Iter first, Iter last)
    {
        for (auto ptr_i = first; ptr_i < last; ptr_i++)
            for (auto ptr_j = ptr_i; ptr_j < last; ptr_j++)
                if (*ptr_i > *ptr_j)
                    std::iter_swap(ptr_i, ptr_j);
    }

    /**
     * @brief Insertion sort.
     *
     * @tparam Iter Vector iterator
     * @param first First vector index to be sorted
     * @param last Last vector index to be sorted
     */
    template<class Iter>
    void insertionSort(Iter first, Iter last)
    {
        std::iter_swap(first, std::min_element(first, last));
        for (Iter key = first; ++key < last; first = key)
            for (Iter elem = key; *elem < *first; --elem, --first)
                std::iter_swap(first, elem);
    }

    /**
     * @brief Print a vector
     *
     * @tparam T Vector type
     * @param vec Vector
     */
    template<class T>
    static void printVector(const std::vector<T>& vec)
    {
        for (const auto& item : vec)
            std::cout << item << " | ";
        std::cout << std::endl;
    }

}


#endif // ALGO_H