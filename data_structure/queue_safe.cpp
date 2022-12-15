#include <array>
#include <iostream>
#include <thread>
#include <chrono>
#include <condition_variable>


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

    {
        // unique_lock prevents mutex from getting locked in case of exception
        std::unique_lock<std::mutex> lock(mutex);
        // The difference between is that you can lock and unlock a std::unique_lock.
        // std::lock_guard will be locked only once on construction and unlocked on destruction.
        // std::unique_lock can also be passed to a function (see below).
        condition.wait(lock, [this]() -> bool
        {
            return (length != 0);
        });
    }

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
    Queue<int, 20> queue;

    std::thread client1 ([&] {
        for (uint i = 0; i < 10; i++){
            if (!queue.isEmpty()) {
                auto item = queue.pop_safe();
                std::cout << "Client1 -> "<< item << std::endl;
            }
            std::this_thread::sleep_for(200ms);
        }
    });

    std::thread client2 ([&] {
        for (uint i = 0; i < 12; i++){
            std::this_thread::sleep_for(300ms);

            auto item = queue.pop_safe();
            std::cout << "Client2 -> "<< item << std::endl;

        }
    });

    std::thread source ([&] {

        for (uint i = 0; i < 20; i++){
            queue.push_safe(i);
        }
        std::this_thread::sleep_for(500ms);

    });

    source.join();
    client1.join();
    client2.join();

    return 0;
}
