#include <stdio.h>
#include <stdlib.h>
#include <iostream>

using namespace std;


/**
 * Allocate memory for an array given the length of the array.
 *
 * @param len Array length.
 * @return pointer to array.
 */
int* allocateArrayMemory(int len) {

    // Return variable
    int* arr;
    // Allocate memory
    arr = (int*) malloc( len * sizeof(len) );

    return arr;
}


/**
 * Populate an array with position number (not index).
 *
 * @param arr Array pointer.
 * @param len Array length.
 */
void populateArray(int* arr, int len) {

    for (int i = 0; i < len; i++) {
        arr[i] =  i + 1;
    }
}


/**
 * Print array values by index.
 *
 * @param arr Array pointer.
 * @param len Array length.
 */
void printArray(int* arr, int len) {

    for (int i = 0; i < len; i++) {
        cout << "Array position " << i << ": " << arr[i] << "\n";
    }
}


int main() {

    // Get length from console
    int length;
    cout << "Insert array length: ";
    cin >> length;

    // Create C style array
    int* arrayC = allocateArrayMemory(length);
    // Create C++ style array
	int* arrayCpp = new int[length];

    // Fill array data
	populateArray(arrayC, length);
	populateArray(arrayCpp, length);

    // Show array data
    cout << "\n----- Array C -----\n";
    printArray(arrayC, length);

    cout << "\n" << "---- Array C++ ----\n";
    printArray(arrayCpp, length);

    // Deallocate memory block
    free(arrayC);
    delete[] arrayCpp;

    /* Note:
        The most important reason why free() should not be used
        for de-allocating memory allocated using new is that,
        it does not call the destructor of that object while
        delete operator does.
    */

    return 0;
}

