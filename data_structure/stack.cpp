#include <iostream>
#include <string>


typedef unsigned int uint;


/*** DESCRIPTION ***/

template <typename T, uint max=10>      // Define MAX with template because we cannot define array lenght during constructor
class Stack
{
 public:
    Stack () : arr{}, height(0) {};
    ~Stack () {};                           // Template is not repeatede during for definition inside the description scope.

    bool isEmpty() { return (height == 0); };
    bool isFull() { return (height == max); };
    uint getSize() { return height; };

    void print();
    bool push(const T& item);
    T    pop();
    T    peek();
 private:
    T arr[max];
    uint height;
};


/*** DEFINITION ***/

template <typename T, uint max>
void Stack<T, max>::print()
{
    if (isEmpty()){
        std::cout << "STACK EMPTY";
    }
    else {
        std::cout << "STACK: | ";
        for (int i = 0; i < height; i++) {
        std::cout << arr[i] << " | ";
        }
    }
    std::cout << std::endl;
}


template <typename T, uint max>     // Template must be repetade during definition outside descripiton scope.
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


template <typename T, uint max>
T Stack<T, max>::pop()
{
    T item{};

    if ( isEmpty() ) {
        std::cout << "The stack is empty!" << std::endl;
    }
    else {
        item = std::move(arr[--height]);
        arr[height] = T{};      // Optional
    }

    return item;
}


template <typename T, uint max>
T Stack<T, max>::peek()
{
    T item{};

    if ( isEmpty() ) {
        std::cout << "The stack is empty!" << std::endl;
    }
    else {
        item = arr[height-1];
    }

    return item;
}




int main() {

    Stack<int, 5> stack05;
    Stack<int> stack10;

    // Push data
    for (int i = 0; i < 10; i++) {

        if (!stack05.isFull()) {
            stack05.push(i+1);
            stack05.print();
        }

        if (!stack10.isFull())
            stack10.push(i+1);
    }

    stack10.print();

    // Check peek
    std::cout << "Stack10 peek is: " << stack10.peek() << std::endl;

    // Pop data
    while (stack10.getSize() > 0) {

        if (!stack05.isEmpty()) {
            auto item05 = stack05.pop();
            std::cout << "Value " << item05 << " popped from stack05." << std::endl;
        }

        if (!stack10.isEmpty()) {
            auto item10 = stack10.pop();
            std::cout << "Value " << item10 << " popped from stack10." << std::endl;
        }

    }

    stack05.print();
    stack10.print();

    return 0;
}
