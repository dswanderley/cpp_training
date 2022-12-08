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


    return 0;
}