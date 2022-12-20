#include <iostream>
#include <iomanip>
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
    ParallelSum(const std::vector<uint64_t>& vec, uint nT);
    ~ParallelSum();

    void join();
    void run();
    int64_t getSum() const { return totalSum; }
    bool getFinish() const;

  private:
    const std::vector<uint64_t> vecData;
    std::vector<bool> vecFinish;
    std::vector<std::thread> vecThreads;
    uint nThreads;
    std::atomic<int64_t> totalSum;
    std::atomic_bool waiting;
    std::mutex mtx;
    std::condition_variable cond;

    void sumFcn(uint start, uint end, uint thd_idx);
    void startThreads();
};

ParallelSum::ParallelSum(const std::vector<uint64_t>& vec, uint nT) :
    vecData(vec), nThreads(nT),
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
    // Initial variables
    uint64_t len = 1'000'000'000;          // Array size
    uint maxThreads = std::thread::hardware_concurrency();
    std::vector<uint64_t> data(len, 1);

    // Iterate for different number of threads
    for (uint nThds = 1; nThds <= maxThreads; nThds++)
    {
        // Start threads
        auto t0 = high_resolution_clock::now();
        ParallelSum pSum(data, nThds);

        // Start to sum
        auto t1 = high_resolution_clock::now();
        pSum.run();

        // Wait for threads sum
        while (!pSum.getFinish()) { ; }
        auto t2 = high_resolution_clock::now();

        // Close threads
        pSum.join();
        auto t3 = high_resolution_clock::now();

        // Calculate processes duration
        auto tTotal = duration_cast<milliseconds>(t3-t0);
        auto tSum = duration_cast<milliseconds>(t2-t1);

        // Print results
        std::cout << "Number of threads: " << std::setw(2) << std::setfill(' ') << nThds << "   |   ";
        std::cout << "Sum result: " << pSum.getSum() << "   |   ";
        std::cout << "Summation time: " << std::setw(4) << std::setfill(' ') << tSum.count() << " ms" << "   |   ";
        std::cout << "Total time: " << std::setw(5) << std::setfill(' ') << tTotal.count() << " ms" << std::endl;
    }

    return 0;
}