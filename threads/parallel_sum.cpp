#include <iostream>
#include <algorithm>
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
    void sumFcn(uint start, uint end, uint thd_idx);
    void join();
    void run();
    int64_t getSum() { return totalSum; }
    bool getFinish() const;

  private:
    std::vector<uint> vecData;
    std::vector<bool> vecFinish;
    std::vector<std::thread> vecThreads;
    uint nThreads;
    std::atomic<int64_t> totalSum;
    std::atomic_bool waiting;
    std::mutex mtx;
    std::condition_variable cond;

    void startThreads();
};

ParallelSum::ParallelSum(uint length, uint nT) :
    vecData(length, 1), nThreads(nT),
    vecFinish(nT, false), totalSum{0}, waiting{true}
{
    startThreads();
}

ParallelSum::~ParallelSum()
{
}

void ParallelSum::sumFcn(uint start, uint end, uint thd_idx)
{
    // Wait for waiting false
    {
        std::unique_lock<std::mutex> lock(mtx);
        cond.wait(lock, [this]() -> bool
        {
            return (!waiting);
        });
    }

    {
        // Sum locally
        int64_t localSum = 0;
        for (uint i=start; i <= end; i++)
        {
            localSum += vecData[i];
        }
        // Update total
        totalSum += localSum;

        vecFinish[thd_idx] = true;
    }
}

void ParallelSum::startThreads()
{
    const uint batch_len = static_cast<uint>(vecData.size() / nThreads);  // batch length
    uint remainder = static_cast<uint>(vecData.size() % nThreads);  // remainder of the division
    uint end=0, rem;                                     // Positions

    for (uint t=0; t < nThreads; t++ )
    {
        // Set extra (rem) value and decrease remainder positions
        if (remainder > 0)  { remainder--; rem = 1; }
        else { rem = 0; }
        // Set star and end
        const uint start = (t==0) ? 0 : end + 1;
        end = start + (batch_len - 1) + rem;

        vecThreads.push_back(std::thread(&ParallelSum::sumFcn, this, start, end, t));
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


bool ParallelSum::getFinish() const
{
    bool res = std::all_of(vecFinish.begin(), vecFinish.end(), [](bool v) { return v; });

    return res;
}

int main()
{

    uint len = 12;

    auto t0 = high_resolution_clock::now();
    ParallelSum pSum(len, 5);

    auto t1 = high_resolution_clock::now();
    pSum.run();

    while (pSum.getFinish())
    {
        ;
    }
    auto t2 = high_resolution_clock::now();

    pSum.join();
    auto t3 = high_resolution_clock::now();


    auto tTotal = duration_cast<milliseconds>(t3-t0);
    auto tSum = duration_cast<milliseconds>(t1-t2);


    std::cout << "Sum result: " << pSum.getSum() << "   |   ";
    std::cout << "sum time: " << tSum.count() << " ms" << "   |   ";
    std::cout << "total time: " << tTotal.count() << " ms";

    return 0;

}