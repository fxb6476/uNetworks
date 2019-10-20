/*
 * Felix Blanco
 * - Set of strucs, definitions, and initializations for building and manipulating matrix's.
 * - ToDO
 * 1)
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
int initMatrix_Random(matrix *mat);
int initMatrix_Ones(matrix *mat);

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
matrix * addMatrix(matrix *m1, matrix *m2);
matrix * addScalar(matrix *m1, float d2);

//Subtracts m1 and m2 like so
// m1 = m1 - m2
matrix * subMatrix(matrix *m1, matrix *m2);
matrix * subScalar(matrix *m1, float d2);

//Multiply m1 and m2 like so
// m1 = m1 * m2
matrix * elementMult(matrix *m1, matrix *m2);
matrix * dotMatrix(matrix *m1, matrix *m2);
matrix * mulScalar(matrix *m1, float d2);

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
int flatHorizMatrix(matrix *m1);
int flatVertMatrix(matrix *m1);

#endif
