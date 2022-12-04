#include <stdio.h>
#include <stdlib.h>
#include <iostream>

using namespace std;


/**
 * Allocate memory for a matrix given its size.
 *
 * @param rows    Number of rows.
 * @param columns Number of columns.
 * @return pointer to matrix.
 */
int** allocateMatrixMemoryC(int rows, int columns) {

    // Return variable
    int **matrix;
    // Allocate memory for rows
    matrix = (int**) malloc( rows * sizeof(int*) );
    // Allocate memory for columns
    for (int i=0; i < rows; i++)
        matrix[i] = (int*) malloc( columns * sizeof(int) );

    return matrix;
}


/**
 * Free memory for a matrix given its size.
 *
 * @param rows  Number of rows.
 * @return      pointer to matrix.
 */
void freeMatrix(int** arr, int rows) {

    // Iterate rows
    for (int i = 0; i < rows; i++) {
        // Free each column pointer
        free(arr[i]);
    }
    // Free rows pointer
    free(arr);
}


/**
 * Populate a 2D matrix with linear indi2ces.
 *
 * @param arr     Matrix.
 * @param rows    Number of rows.
 * @param columns Number of columns.
 */
void populateArray(int** arr, int rows, int columns) {

    // Iterate rows
    for (int i = 0; i < rows; i++) {
        // Iterate columns
        for (int j = 0; j < columns; j++) {
            arr[i][j] =  i*columns + j + 1;
        }
    }
}


/**
 * Print array values by index.
 *
 * @param arr     Matrix.
 * @param rows    Number of rows.
 * @param columns Number of columns.
 */
void printMatrix(int** arr, int rows, int columns) {

    // Iterate columns
    for (int j = 0; j < columns; j++) {
        // Iterate rows
        for (int i = 0; i < rows; i++) {
            if (arr[i][j] < 10)
                cout << " 0" << arr[i][j] << " "; // Add zero to keep to digits
            else
                cout << " " << arr[i][j] << " ";
        }
        // Break line (end of a row)
        cout << "\n";
    }
}


/**
 * MAIN FUNCTION
*/
int main() {

    // Get length from console
    int rows, columns;
    cout << "Insert number of rows: ";
    cin >> rows;
    cout << "Insert number of columns: ";
    cin >> columns;

    // Create C style matrix
    int** matrixC = allocateMatrixMemoryC(rows, columns);

    // Fill array data
	populateArray(matrixC, rows, columns);

    // Show array data
    cout << "\n Matrix C \n";
    printMatrix(matrixC, rows, columns);

    // Deallocate memory block
    freeMatrix(matrixC, rows);

    return 0;
}

