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
    int *arr;
    // Allocate memory
    arr = (int*) malloc( len * sizeof(len) );

    return arr;
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

    // Create C style malloc array
    int* arrayMalloc = (int*) malloc( length * sizeof(int) );

    // Create C style malloc array
    int* arrayCalloc = (int*) calloc(length, sizeof(int));

    // Create C++ style array
	int* arrayCpp = new int[length];

    // Create C++ style array with 0s
	int* arrayCpp0s = new int[length] ();

    // Show array data
    cout << "\n--- Array C malloc ---\n";
    printArray(arrayMalloc, length);

    // Show array data
    cout << "\n--- Array C calloc ---\n";
    printArray(arrayCalloc, length);

    cout << "\n" << "------ Array C++ ------\n";
    printArray(arrayCpp, length);

    cout << "\n" << "----- Array C++ 0 -----\n";
    printArray(arrayCpp0s, length);

    // Deallocate memory block
    free(arrayMalloc);
    free(arrayCalloc);
    delete[] arrayCpp;
    delete[] arrayCpp0s;

    return 0;
}

