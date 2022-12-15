#include <array>
#include <iostream>


typedef unsigned int uint;


template<class T, uint size=10>
class Queue
{
private:
    std::array<T, size> queue;
    uint length;
public:
    Queue() : length(0), queue{} {};
    ~Queue() {};

    bool isEmpty() { return (length == 0); };
    bool isFull() { return (length == size); };
    T lookFirst() { return queue[0]; }

    void print();

    T& operator[](uint index);
};


template<class T, uint size>
void Queue<T, size>::print()
{
     if (isEmpty()){
        std::cout << "QUEUE EMPTY";
    }
    else {
        std::cout << "QUEUE: | ";
        for (int i = 0; i < length; i++) {
        std::cout << queue[i] << " | ";
        }
    }
    std::cout << std::endl;
}

template<class T, uint size>
T& Queue<T, size>::operator[](uint index) {
    // Check index
    if (index >= length){
        std::cout << "Array index out of bound.";
        exit(0);
    }

    return queue[index];
}


int main()
{


    return 0;
}
