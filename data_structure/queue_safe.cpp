#include <array>
#include <iostream>
#include <thread>
#include <chrono>
#include <condition_variable>


typedef unsigned int uint;


template<class T, uint size=10>
class Queue
{
 public:
    Queue() : queue{}, length(0) {}
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

    return std::move(item);
}

template<class T, uint size>
T Queue<T, size>::pop_safe()
{

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
    Queue<int, 5> queue;

    int i = 1;

    while (!queue.isFull()) {
        if (queue.push(i++))
            queue.print();
    }
    //queue.push(i++);

    while (!queue.isEmpty()) {
        bool empty = queue.isEmpty();
        auto item = queue.pop();
        std::cout << "Value " << item << " popped." << std::endl;
        queue.print();
    }
    //auto item = queue.pop();

    return 0;
}
