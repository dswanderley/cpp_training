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
     * Bubble Sort is the simplest sorting algorithm that works by repeatedly
     * swapping the adjacent elements if they are in the wrong order.
     * This algorithm is not suitable for large data sets as its average and
     * worst-case time complexity is quite high.
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
     * This algorithm is one of the simplest algorithm with simple implementation
     * The array is virtually split into a sorted and an unsorted part.
     * Values from the unsorted part are picked and placed at the correct
     * position in the sorted part.
     * It is appropriate for data sets which are already partially sorted.
     *
     * @tparam Iter Vector iterator
     * @param first First vector index to be sorted
     * @param last Last vector index to be sorted
     */
    template<class Iter>
    void insertionSort(Iter first, Iter last)
    {
        std::iter_swap(first, std::min_element(first, last)); // pick the smallest element in the range and swap
        for (Iter key = first; ++key < last; first = key)
            for (Iter elem = key; *elem < *first; --elem, --first)
                std::iter_swap(first, elem);
    }

    /**
     * @brief Selection sort algorthim
     * The selection sort algorithm sorts an array by repeatedly finding the
     *  minimum element (considering ascending order) from the unsorted part
     *  and putting it at the beginning.
     *
     * @tparam Iter Vector iterator
     * @param first First vector index to be sorted
     * @param last Last vector index to be sorted
     */
    template<class Iter>
    void selectionSort(Iter first, Iter last)
    {
        for(Iter el = first; el != last; el++)
            std::iter_swap(el, std::min_element(el, last)); // pick the smallest element in the range and swap
    }

    /**
     * @brief Quick Sort
     * Based on the divide and conquer paradigm, tt picks an element as a pivot
     *  and partitions the given array around the picked pivot. The key process
     *  in quickSort is the partition.
     *
     * @tparam Iter Vector iterator
     * @param first First vector index to be sorted
     * @param last Last vector index to be sorted
     */
    template<class Iter>
    void quickSort(Iter first, Iter last)
    {
        if (first < last)
        {
            // Partition
            Iter middle = first + 1;
            for (Iter el = first + 1; el < last; el++)
            {
                if (*el < *first) // Compare with pivot
                {
                    std::iter_swap(el, middle);
                    middle++;
                }
            }
            // Separately sort elements before
            // partition and after partition
            std::iter_swap(first, middle-1);
            quickSort(first, middle-1);
            quickSort(middle, last);
        }
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