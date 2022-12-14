#include <iostream>
#include <string>


/*** DESCRIPTION ***/

template <typename T>
class Stack
{
private:
    /* data */
public:
    Stack (/* args */);
    ~Stack ();
                // Template is not repeatede during for definition inside the description scope.
};


/*** DEFINITION ***/

template <typename T>           // Template must be repetade during definition outside descripiton scope.
Stack<T>::Stack(/* args */)
{
}

template <typename T>
Stack<T>::~Stack()
{
}



int main() {


    return 0;
}
