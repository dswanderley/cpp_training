#include <iostream>
#include <vector>
#include <chrono>
#include <atomic>
#include <thread>
#include <mutex>
#include <condition_variable>

using namespace std::chrono;

typedef unsigned int uint;


class ParallelSum
{

  public:
    ParallelSum(uint lenght, uint nT);
    ~ParallelSum();
    void sumFcn(uint start, uint end);
    void join();
    void run();

  private:
    std::vector<std::thread> vecThreads;
    std::vector<uint> vecData;
    uint nThreads;
    std::atomic_bool waiting{true};
    std::mutex mtx;
    std::condition_variable cond;

    void startThreads();
};

ParallelSum::ParallelSum(uint length, uint nT) : vecData(length, 0), nThreads(nT)
{
    startThreads();
}

ParallelSum::~ParallelSum()
{
}

void ParallelSum::sumFcn(uint start, uint end)
{
    // Wait for waiting false
    {
        // unique_lock prevents mutex from getting locked in case of exception
        std::unique_lock<std::mutex> lock(mtx);
        cond.wait(lock, [this]() -> bool
        {
            return (!waiting);
        });
    }

}

void ParallelSum::startThreads()
{
    const uint batch_len = static_cast<uint>(vecData.size() / nThreads);  // batch length
    uint remainder = static_cast<uint>(vecData.size() % nThreads);  // remainder of the division
    uint end=0, rem;                                     // Positions

    for (int t=0; t < nThreads; t++ )
    {
        // Set extra (rem) value and decrease remainder positions
        if (remainder > 0)  { remainder--; rem = 1; }
        else { rem = 0; }
        // Set star and end
        const uint start = (t==0) ? 0 : end + 1;
        end = start + (batch_len - 1) + rem;

        vecThreads.push_back(std::thread(&ParallelSum::sumFcn, this, start, end));
    }
}

void ParallelSum::join()
{
    for (auto& t: vecThreads) t.join();
}

void ParallelSum::run()
{
    // All threads are running but waiting.
    {
        // unique_lock prevents mutex from getting locked in case of exception
        std::unique_lock<std::mutex> lock(mtx);
        waiting = false;
    }
    // Alert all that mutex was released
    cond.notify_all();
}



int main()
{

    uint len = 2^12;

    ParallelSum pSum(len, 1);

    pSum.run();

    pSum.join();


    return 0;

}