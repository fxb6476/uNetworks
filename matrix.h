/*
 * Felix Blanco
 * - Set of strucs, definitions, and initializations for building and manipulating matrix's.
 * - ToDO
 * 1) Make matrix structure
 *   - rows, colmns
 *   - array holding data
 * 2) Array initializer
 * 3) Array destructor
 * 4) Add Arrays
 *    - Add array and scalar
 * 5) Subtract arrays
 *    - Sub array and scalar
 * 6) Dot product
 *    - Multiply array and scalar
 * 7) Transpose
 * 8) Determinant
 * 9) Inverse
 * 9) Pretty print Matrix, for debugging.
 */

#pragma once
#ifndef matrix_h

// Void pointer to data so we can initialize matrix's of doubles, floats, chars, etc, any data type.
typedef struct{
    int row;
    int col;
    int data_size;
    int data_type; // 0 - int, 1 - double, 2 - float, 3 - char, 4 - long, anything else - int.
    void *data;
}matrix;

//Pass in a matrix and initialize its data to all zeros.
int initMatrix_Zeros(matrix *mat);

//Initialize a matrix with data passed in.
//If data is too small to fill the matrix, then 0's will be appended, where their is no data.
//Data is pushed to top left of matrix
int initMatrix_Data(matrix *mat, void *dat);

//Pointer to matrix so we can free the data at '**data'
// Returns 0 for success, -1 for failure.
int delMatrix(matrix *mat);

//Adds m1 and m2 like so
// m1 = m1 + m2
// Pass 0 for type matrix, 1 for other, int, float, double, etc.
int addMatrix(matrix *m1, void *m2, int type);

//Subtracts m1 and m2 like so
// m1 = m1 - m2
// Pass 0 for type matrix, 1 for other, int, float, double, etc.
int subMatrix(matrix *m1, void *m2, int type);

//Multiply m1 and m2 like so
// m1 = m1 * m2
// Pass 0 for type matrix, 1 for other, int, float, double, etc.
int mulMatrix(matrix *m1, void *m2, int type);

//Transpose matrix that is passed in.
int transMatrix(matrix *m1);

//Output the determinant
float determineMatrix(matrix *m1);

//Crappy way of computing the inverse of a matrix.
//The inverse is computed using the 'minor matrix method'.
matrix invertMatrix(matrix *m1);

//Does a 'pretty' print of the matrix, for debugging purposes.
void printMatrix(matrix *m1);

#endif
