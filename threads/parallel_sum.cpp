#include <iostream>
#include <vector>
#include <chrono>
#include <atomic>
#include <thread>
#include <mutex>
#include <future>

using namespace std::chrono;

typedef unsigned int uint;



void soma(){}


class ParallelSum
{

  public:
    ParallelSum(uint lenght, uint nT);
    ~ParallelSum();
    void sumFcn(uint start, uint end);

  private:
    std::vector<std::thread> vecThreads;
    std::vector<uint> vecData;
    uint nThreads;
};

ParallelSum::ParallelSum(uint length, uint nT) : vecData(length, 0), nThreads(nT)
{
    vecThreads = std::vector<std::thread>(nThreads);

    uint interval = static_cast<uint>(length / nThreads);
    uint remainder = static_cast<uint>(length % nThreads);

    for (int t=0; t < nThreads; t++ )
    {
        uint start, end;



        auto thd = std::thread(&ParallelSum::sumFcn, this, start, end);

        vecThreads

        thd.join();
    }


}

ParallelSum::~ParallelSum()
{
}

void ParallelSum::sumFcn(uint start, uint end)
{

}

int main()
{

    uint len = 2^12;

    ParallelSum pSum(len, 1);


    return 0;

}