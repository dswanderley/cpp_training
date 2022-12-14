#include <iostream>
#include <string>


/*** DESCRIPTION ***/

template <typename T, unsigned int max=10>      // Define MAX with template because we cannot define array lenght during constructor
class Stack
{
private:
    T arr[max];
    unsigned int height;
public:
    Stack () : height(0), arr{} {};
    ~Stack () {};                           // Template is not repeatede during for definition inside the description scope.

    bool isEmpty() { return (height == 0); };
    bool isFull() { return (height == max); };
    unsigned int getSize() { return height; };

    bool push(const T& item);
    T    pop();
    T    peek();
};


/*** DEFINITION ***/

template <typename T, unsigned int max>     // Template must be repetade during definition outside descripiton scope.
bool Stack<T, max>::push(const T& item)
{
    return true;
}


template <typename T, unsigned int max>
T Stack<T, max>::pop()
{
    return true;
}


int main() {

    Stack<int, 5> myStack;

    Stack<int> stack;

    return 0;
}
