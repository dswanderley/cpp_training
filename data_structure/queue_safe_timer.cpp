#include <array>
#include <iostream>
#include <thread>
#include <chrono>
#include <mutex>
#include <condition_variable>
#include <atomic>


using namespace std::chrono_literals;


typedef unsigned int uint;


template<class T, uint size=10>
class Queue
{
 public:
    Queue() : queue{}, mutex{}, condition{}, length(0) {}
    ~Queue() {}

    T lookFirst() const { return queue[0]; }
    uint getLength() { return length; }
    bool isEmpty() const { return (length == 0); }
    bool isFull() const { return (length == size); }

    T& operator[](uint index) const;
    T pop();
    T pop_safe();
    bool push(const T& item);
    bool push_safe(const T& item);
    void print() const;

 private:
    std::array<T, size> queue;
    mutable std::mutex mutex;
    std::condition_variable condition;
    uint length;
};


template<class T, uint size>
T& Queue<T, size>::operator[](uint index) const
{
    // Check index
    if (index >= length){
        std::cout << "Array index out of bound.";
        exit(0);
    }

    return queue[index];
}

template<class T, uint size>
T Queue<T, size>::pop()
{
    T item{};

    if (length == 0) {
        std::cout << "EMPTY QUEUE!" << std::endl;
    }
    else {
        item = std::move( queue[0] );

        for (uint i = 0; i < length; i++) {
            queue[i] = std::move( queue[i+1] );
        }

        length--;
    }

    return item;
}

template<class T, uint size>
T Queue<T, size>::pop_safe()
{
    // Wait for length > 0
    {
        // unique_lock prevents mutex from getting locked in case of exception
        std::unique_lock<std::mutex> lock(mutex);
        // The difference between is that you can lock and unlock a std::unique_lock.
        // std::lock_guard will be locked only once on construction and unlocked on destruction.
        // std::unique_lock can also be passed to a function (see below).
        condition.wait_for(lock, std::chrono::milliseconds(1000), [this]() -> bool
        {
            return (length != 0);
        });
    }
    // Pop
    {
        std::unique_lock<std::mutex> lock(mutex);
        const T item = pop();

        return item;
    }
}

template<class T, uint size>
bool Queue<T, size>::push(const T& item)
{
    bool pushed = false;

    if (length != size) {
        queue[length] = item;
        length++;
        pushed = true;
    }
    else {
        std::cout << "FULL QUEUE!" << std::endl;
    }

    return pushed;
}

template<class T, uint size>
bool Queue<T, size>::push_safe(const T& item)
{
    bool pushed = false;
    {
        // unique_lock prevents mutex from getting locked in case of exception
        std::unique_lock<std::mutex> lock(mutex);
        pushed = push(item);
    }
    // Alert all that mutex was released
    condition.notify_all();

    return pushed;
}

template<class T, uint size>
void Queue<T, size>::print() const
{
     if (isEmpty()) {
        std::cout << "This queue is empty.";
    }
    else {
        std::cout << "QUEUE: | ";
        for (int i = 0; i < length; i++) {
        std::cout << queue[i] << " | ";
        }
    }
    std::cout << std::endl;
}


int main()
{
    Queue<int, 100> queue;
    std::atomic_bool running{true};
    std::mutex mtx_print;

    int c1=0, c2=0;

    std::thread client1 ([&] {
        while (running)
        {
            auto item = queue.pop_safe();
            // Safe guard print out
            {
                std::lock_guard<std::mutex> lock(mtx_print);
                std::cout << "Client1 -> "<< item << std::endl;
            }
            c1 += item != 0 ? 1 : 0;
            std::this_thread::sleep_for(201ms);
        }
    });

    std::thread client2 ([&] {
        while (running)
        {
            std::this_thread::sleep_for(200ms);
            auto item = queue.pop_safe();
            c2 += item != 0 ? 1 : 0;
            // Safe guard print out
            {
                std::lock_guard<std::mutex> lock(mtx_print);
                std::cout << "Client2 -> "<< item << std::endl;
            }
        }
    });

    std::thread source ([&] {

        for (uint i = 1; i < 101; i++) {
            queue.push_safe(i);
            std::this_thread::sleep_for(100ms);
        }
        std::this_thread::sleep_for(300ms);
        running = false;
    });

    source.join();
    client1.join();
    client2.join();

    std::cout << std::endl;
    std::cout << "c1: " << c1 << std::endl;
    std::cout << "c2: " << c2 << std::endl;

    return 0;
}
