/*
 * Felix Blanco
 * - Set of strucs, definitions, and initializations for building and manipulating matrix's.
 * - ToDO
 * 1) Make matrix structure
 *   - rows, colmns, type
 *   - array holding data
 * 2) Matrix initializer
 * 3) Matrix destructor
 * 4) Add Matrix
 *    - Add Matrix and scalar
 * 5) Subtract Martix
 *    - Sub matrix and scalar
 * 6) Dot product
 *    - Multiply Matrix and scalar
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
    float **data;
}matrix;

//Pass in a matrix and initialize its data to all zeros.
int initMatrix_Zeros(matrix *mat);

//Initialize a matrix with data passed in.
//If data is too small to fill the matrix, then 0's will be appended, where their is no data.
//Data is pushed to top left of matrix
int initMatrix_Data(matrix *mat, float dat[][3], int row, int col);

//Initializes matrix to identity matrix, pushed to top left...
int initMatrix_Identity(matrix *mat);

//Pointer to matrix so we can free the data at '**data'
// Returns 0 for success, -1 for failure.
int delMatrix(matrix *mat);

//Clone one matrix into another.
// m1 == m2
int cloneMatrix(matrix *m1, matrix *m2);

//Adds m1 and m2 like so
// m1 = m1 + m2
int addMatrix(matrix *m1, matrix *m2);
int addScalar(matrix *m1, float d2);

//Subtracts m1 and m2 like so
// m1 = m1 - m2
int subMatrix(matrix *m1, matrix *m2);
int subScalar(matrix *m1, float d2);

//Multiply m1 and m2 like so
// m1 = m1 * m2
int dotMatrix(matrix *m1, matrix *m2);
int mulScalar(matrix *m1, float d2);

//Transpose matrix that is passed in.
int transMatrix(matrix *m1);

//Output the determinant
//Crappy, slow way using laplace expantion.
float determineMatrix(matrix *m1);

//Crappy way of computing the inverse of a matrix.
//The inverse is computed using the 'minor matrix method'.
//matrix invertMatrix(matrix *m1);

//Does a 'pretty' print of the matrix, for debugging purposes.
void printMatrix(matrix *m1);

//Reshape takes in a matrix and rearranges it to another architecture.
//Reads the matrix from top left to bottom right...
/*
    The reshaping will fail if the new rows and cols values,
    do not equal the number of original entries.
    --- og_rows * og_cols === new_rows *new_cols
*/
int reshapeMatrix(matrix *m1, int n_rows, int n_cols);

#endif
