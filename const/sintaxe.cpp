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

    int const c1 = 1;
    std::cout << "Const x = " << c1 << std::endl;

    // or
    const int c2 = 2;
    std::cout << "Const y = " << c2 << std::endl;


    return 0;
}