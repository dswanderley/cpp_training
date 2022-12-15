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

    void print();
};


template<class T, uint size>
void Queue<T, size>::print()
{

}



int main()
{


    return 0;
}
