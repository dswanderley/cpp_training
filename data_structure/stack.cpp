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
    Stack ();
    ~Stack ();
                // Template is not repeatede during for definition inside the description scope.
};


/*** DEFINITION ***/

template <typename T, unsigned int max>           // Template must be repetade during definition outside descripiton scope.
Stack<T, max>::Stack() : height(0), arr{}
{
}

template <typename T, unsigned int max>
Stack<T, max>::~Stack()
{
}



int main() {

    Stack<int, 5> myStack;

    Stack<int> stack;

    return 0;
}
