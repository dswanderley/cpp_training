#include <algorithm>
#include <functional>
#include <iostream>
#include <vector>
#include <stdint.h>

//  Windows
#ifdef _WIN32

#include <intrin.h>
uint64_t rdtsc(){
    return __rdtsc();
}

//  Linux/GCC
#else

uint64_t rdtsc(){
    unsigned int lo,hi;
    __asm__ __volatile__ ("rdtsc" : "=a" (lo), "=d" (hi));
    return ((uint64_t)hi << 32) | lo;
}

#endif

void printVector(const std::vector<int>& vec)
{
    for (const auto& item : vec)
        std::cout << item << " | ";
    std::cout << std::endl;
}


void printrRDTSC(int64_t t0, int64_t tf)
{
    std::cout << "RTSCD: ";     // Read Time-Stamp Counter Diference
    std::cout << tf-t0 << std::endl;
}



int main()
{
    const int maxVal = 100;
    const int length = 15;
    int64_t t0, tf;

    std::vector<int> data(length);
    std::vector<int> sdata(length);

    std::generate( data.begin(),
                   data.end(),
                   [&]() -> int { return std::rand() % maxVal; }
                 );

    printVector(data);
    std::cout << std::endl;

    /*
     * SORT
     * Sorts a range into ascending order.
     */
    std::cout << "1) Sort Algorithm" << std::endl;
    {
        sdata = data;
        t0 = rdtsc();
        std::sort(sdata.begin(), sdata.end());
        tf = rdtsc();

        printVector(sdata);
        printrRDTSC(t0, tf);
    }
    std::cout << std::endl;

    /*
     * PARTIAL SORT
     * Sorts the first N elements of a range.
     */
    std::cout << "2) Partial Sort Algorithm" << std::endl;
    {
        sdata = data;
        t0 = rdtsc();
        std::partial_sort( sdata.begin(),
                           sdata.begin() + length/2,
                           sdata.end()
                         );
        tf = rdtsc();

        printVector(sdata);
        printrRDTSC(t0, tf);
    }
    std::cout << std::endl;

    /*
     * Nth ELEMENT SORT
     * Partially sorts the given range making sure that
     * it is partitioned by the given element.
     */
    std::cout << "3) Nth Element - middle" << std::endl;
    {
        auto m = data.begin() + data.size()/2;
        sdata = data;
        t0 = rdtsc();
        std::nth_element( sdata.begin(), m, sdata.end() );
        tf = rdtsc();

        printVector(sdata);
        printrRDTSC(t0, tf);
    }

    std::cout << "4) Nth Element - second" << std::endl;
    {
        sdata = data;
        t0 = rdtsc();
        std::nth_element( sdata.begin(), sdata.begin()+1, sdata.end() );
        tf = rdtsc();

        printVector(sdata);
        printrRDTSC(t0, tf);
    }

    std::cout << "5) Nth Element - last" << std::endl;
    {
        sdata = data;
        t0 = rdtsc();
        std::nth_element( sdata.begin(),
                          sdata.begin()+1,
                          sdata.end(),
                          std::greater<int>()
                         );
        tf = rdtsc();

        printVector(sdata);
        printrRDTSC(t0, tf);
    }
    std::cout << std::endl;

    /*
     * INPLACE MERGE
     * Merges two ordered ranges in-place
     */
    std::cout << "6) Inplace Merge" << std::endl;
    {
        auto m = data.size() / 2;

        std::vector<int> sdata1( data.begin(), data.begin() + m );
        std::vector<int> sdata2( data.begin() + m, data.end() );

        std::cout << "Part 1" << std::endl;
        std::sort( sdata1.begin(), sdata1.end() );
        printVector(sdata1);

        std::cout << "Part 2" << std::endl;
        std::sort( sdata2.begin(), sdata2.end() );
        printVector(sdata2);

        std::vector<int> dst(sdata1);
        /*std::merge( sdata1.begin(), sdata1.end(),
                    sdata2.begin(), sdata2.end(),
                     std::back_inserter(dst) );*/

        dst.insert(dst.end(), sdata2.begin(), sdata2.end());

        //auto mid = dst.begin() + (dst.end() + dst.begin())/2;

        //std::inplace_merge(dst.begin(), mid, dst.end());

        //printVector(sdata1);
        printVector(dst);
    }

    return 0;
}