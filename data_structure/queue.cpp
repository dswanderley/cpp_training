#include <array>
#include <iostream>


typedef unsigned int uint;


template<class T, uint size=10>
class Queue
{
 public:
    Queue() : queue{}, length(0) {}
    ~Queue() {}

    bool isEmpty() const { return (length == 0); }
    bool isFull() const { return (length == size); }
    uint getLength() { return length; }
    T lookFirst() const { return queue[0]; }

    T& operator[](uint index) const;
    T pop();
    void push(const T& item);
    void print() const;

 private:
    std::array<T, size> queue;
    uint length;
};


template<class T, uint size>
void Queue<T, size>::print() const
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
void Queue<T, size>::push(const T& item)
{

}

template<class T, uint size>
T Queue<T, size>::pop()
{
    T item{};

    if (length == 0)
    {
        std::cout << "EMPTY QUEUE!" << std::endl;
    }
    else
    {
        item = std::move( queue[0] );

        for (uint i = 0; i < length; i++)
        {
            queue[i] = std::move( queue[i+1] );
        }
        length--;
    }

    return item;
}


int main()
{


    return 0;
}
