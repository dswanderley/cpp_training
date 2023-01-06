#ifndef RDTSC_H
#define RDTSC_H

//  Windows
#ifdef _WIN32

#include <intrin.h>
uint64_t rdtsc()
{
    return __rdtsc();
}

//  Linux/GCC
#else

uint64_t rdtsc()
{
    unsigned int lo,hi;
    __asm__ __volatile__ ("rdtsc" : "=a" (lo), "=d" (hi));
    return ((uint64_t)hi << 32) | lo;
}

#endif

void printrRDTSC(const int64_t t0, const int64_t tf)
{
    std::cout << "RTSCD: ";     // Read Time-Stamp Counter Diference
    std::cout << tf-t0 << std::endl;
}

#endif // RDTSC_H