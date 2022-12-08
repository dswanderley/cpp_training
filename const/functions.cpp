#include <iostream>


/**
 * REFERECENCE:
 *  https://www.cprogramming.com/tutorial/const_correctness.html
*/

/**
 * The const member functions are the functions which are declared as constant in the program.
 * The object called by these functions cannot be modified.
 * It is recommended to use const keyword so that accidental changes to object are avoided.
 *
 * A const member function can be called by any type of object.
 * Non-const functions can be called by non-const objects only.
*/

class MyClass
{
private:
    int v1;
    int v2;
    const int c1;
    const int c2;

public:
    MyClass();
    ~MyClass();

    int get_c1() const { return c1; };
    int get_c2() { return c2; };
    int get_v1() const { return v1; };
    int get_v2() { return v2; };

    int sum(int x) const;
};


MyClass::MyClass() : v1(10), v2(20), c1(1), c2(2)
{
}

MyClass::~MyClass()
{
}

int MyClass::sum(int x) const
{
    int y = x + v1;

    // v2 = y;  /* error: assignment of member 'MyClass::v2' in read-only object */

    return y;
}


int main() {

    MyClass vObj;
    const MyClass cObj;

    // Test variable case
    std::cout << "vObject v1 is " << vObj.get_v1() << std::endl; // const method
    std::cout << "vObject v2 is " << vObj.get_v2() << std::endl; // non-const method
    std::cout << "vObject c1 is " << vObj.get_c1() << std::endl; // const method
    std::cout << "vObject c2 is " << vObj.get_c2() << std::endl; // non-const method
    std::cout << "vObject sum to 10 is " << vObj.sum(10) << std::endl; // const method

    // Test const case
    std::cout << "cObj v1 is " << cObj.get_v1() << std::endl; // const method
    // std::cout << "cObj v2 is " << cObj.get_v2() << std::endl; /* error: passing 'const MyClass' as 'this' argument discards qualifiers [-fpermissive] */
    std::cout << "cObj c1 is " << cObj.get_c1() << std::endl; // const method
    // std::cout << "cObj c2 is " << cObj.cObj() << std::endl; /* error: passing 'const MyClass' as 'this' argument discards qualifiers [-fpermissive */
    std::cout << "cObj sum to 10 is " << vObj.sum(10) << std::endl; // const method

    return 0;
}