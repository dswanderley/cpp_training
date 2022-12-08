#include <iostream>



/**
 * REFERECENCE:
 *  https://www.cprogramming.com/tutorial/const_correctness.html
*/


int main() {

    int const c1 = 1;
    const int c2 = 2;

    /**
     *  POINTERS
     */

    /* POINTER TO CONSTANT DATA */
    const int *p_cint;          // *p_cint is a "const int" - usually refer as "const pointer" - works as a reader

    // CASE 1 - point to const
    p_cint = &c1;
    std::cout << "p_cint (" << &p_cint << ")" << std::endl;
    std::cout << "Pointer to: " << p_cint << ", value: " << *p_cint << std::endl;

    // CASE 2 - change to another const
    p_cint = &c2;
    std::cout << "p_cint (" << &p_cint << ")" << std::endl;
    std::cout << "Pointer to: " << p_cint << ", value: " << *p_cint << std::endl;

    // CASE 3 - change const value
    // *p_cint = 10;    /* error: assignment of read-only location '* p_cint' */

    // CASE 4 - point to a variable
    int v1 = 12;

    p_cint = &v1;
    std::cout << "p_cint (" << &p_cint << ")" << std::endl;
    std::cout << "Pointer to: " << p_cint << ", value: " << *p_cint << std::endl;

    // CASE 5 - Change variable value
    // *p_cint = 10;    /* error: assignment of read-only location */


    /* CONSTANT POINTER */
    int v2 = 0;

    // Point to a variable
    int * const pc_int = &v2;         // Address stored cannot be changed, only data - works as a fixed watcher that can modify the data
    std::cout << "p_int (" << &pc_int << ")" << std::endl;
    std::cout << "Pointer to: " << pc_int << ", value: " << *pc_int << std::endl;

    // Changing variable value
    *pc_int = 50;
    std::cout << "p_int (" << &pc_int << ")" << std::endl;
    std::cout << "Pointer to: " << pc_int << ", value: " << *pc_int << std::endl;

    // Change pointed variable/address.
    // pc_int = &a; /* error: assignment of read-only variable 'p_int'*/

    // Point to a const
    // int * const pc_int = &x; /* error: invalid conversion from 'const int*' to 'int*' [-fpermissive] */


    /* CONSTANT POINTER TO CONSTANT DATA */

    // CASE 1 - Point to const
    const int * const pc_cint1 = &c1;
    std::cout << "pc_cint1 (" << &pc_cint1 << ")" << std::endl;
    std::cout << "Pointer to: " << pc_cint1 << ", value: " << *pc_cint1 << std::endl;

    // CASE 2 - Change pointed const/address.
    // pc_cint1 = &c2;      /* error: assignment of read-only variable 'pc_cint1' */

    // CASE 3 - Change const value
    // *pc_cint1 = 50;      /* error:  error: assignment of read-only location '*(const int*)pc_cint1' */

    // CASE 4 - Point to variable
    const int * const pc_cint2 = &v1;
    std::cout << "pc_cint2 (" << &pc_cint2 << ")" << std::endl;
    std::cout << "Pointer to: " << pc_cint2 << ", value: " << *pc_cint2 << std::endl;

    // CASE 5 - Change pointed variable/address.
    // pc_cint2 = &v2;     /* error: assignment of read-only variable 'pc_cint2' */

    // CASE 6 - Change variable value
    // *pc_cint2 = 50;     /* error: assignment of read-only location '*(const int*)pc_cint2' */

    return 0;
}