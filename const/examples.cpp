#include <stdio.h>
#include <stdlib.h>
#include <iostream>



/**
 * REFERECENCE:
 *  https://www.cprogramming.com/tutorial/const_correctness.html
*/


int main() {

    /**
    * SINTAXE
    */

    int const x = 1;
    std::cout << "Const x = " << x << std::endl;

    // or
    const int y = 2;
    std::cout << "Const y = " << y << std::endl;


    /**
     *  POINTERS
     */

    /* POINTER TO CONSTANT DATA */
    const int *p_cint;          // *p_cint is a "const int" - usually refer as "const pointer"

    // Case 1 - point to const
    p_cint = &x;
    std::cout << "p_cint (" << &p_cint << ")" << std::endl;
    std::cout << "Pointer to: " << p_cint << ", value: " << *p_cint << std::endl;

    // Case 2 - change to another const
    p_cint = &y;
    std::cout << "p_cint (" << &p_cint << ")" << std::endl;
    std::cout << "Pointer to: " << p_cint << ", value: " << *p_cint << std::endl;

    // Case 3 - change const value
    // *p_cint = 10;    /* error: assignment of read-only location '* p_cint' */

    // Case 4 - point to a variable
    int a = 12;

    p_cint = &a;
    std::cout << "p_cint (" << &p_cint << ")" << std::endl;
    std::cout << "Pointer to: " << p_cint << ", value: " << *p_cint << std::endl;

    // Case 5 - Change variable value
    // *p_cint = 10;    /* error: assignment of read-only location */


    /* CONSTANT POINTER */
    int b = 0;

    // Point to a variable
    int * const p_int = &b;         // Address stored cannot be changed, only data
    std::cout << "p_int (" << &p_int << ")" << std::endl;
    std::cout << "Pointer to: " << p_int << ", value: " << *p_int << std::endl;

    // Changing variable value
    *p_int = 50;
    std::cout << "p_int (" << &p_int << ")" << std::endl;
    std::cout << "Pointer to: " << p_int << ", value: " << *p_int << std::endl;

    // Change pointed variable/address.
    // p_int = &a; /* error: assignment of read-only variable 'p_int'*/

    // Point to a const
    // int * const p2_int = &x; /* error: invalid conversion from 'const int*' to 'int*' [-fpermissive] */

    return 0;
}