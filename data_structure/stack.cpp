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
    bool ret;

    if ( isFull() ) {
        std::cout << "The stack is full!" << std::endl;
        ret = false;
    }
    else{
        arr[height++] = item;
        ret = true;
    }

    return ret;
}


template <typename T, unsigned int max>
T Stack<T, max>::pop()
{
    T item{};

    if ( isEmpty() ) {
        std::cout << "The stack is empty!" << std::endl;
    }
    else {
        item = std::move(arr[--height]);
    }

    return item;
}


int main() {

    Stack<int, 5> myStack;

    Stack<int> stack;

    int a = 5;
    int b = 5;

    return 0;
}
