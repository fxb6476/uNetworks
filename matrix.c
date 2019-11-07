#include <stdio.h>
#include <string.h>
#include <time.h>
#include <math.h>
#include <stdlib.h>
#include "matrix.h"

//Matrix Init Functions ------------------------------------------------------------------------------------------------
int initMatrix_Zeros(matrix *mat){
    mat->data = (float **)calloc(mat->row, sizeof(float *));

    if(!mat->data){
        printf("Error allocating main data array!\n");
        return -1;
    }

    for(int i = 0; i < mat->row; i++) {
        mat->data[i] = (float *)calloc(mat->col, sizeof(float));
        if(!mat->data){
            printf("Error allocating sub array in data #%d!\n", i);
            return -1;
        }
    }

    for(int i=0; i < mat->row; i++){
        for(int j=0; j < mat->col; j++){
            mat->data[i][j] = 0.0;
        }
    }
    return 0;
}
int initMatrix_Random(matrix *mat){

    srand((long)time(NULL));

    mat->data = (float **)calloc(mat->row, sizeof(float *));

    if(!mat->data){
        printf("Error allocating main data array!\n");
        return -1;
    }

    for(int i = 0; i < mat->row; i++) {
        mat->data[i] = (float *)calloc(mat->col, sizeof(float));
        if(!mat->data){
            printf("Error allocating sub array in data #%d!\n", i);
            return -1;
        }
    }

    for(int i=0; i < mat->row; i++){
        for(int j=0; j < mat->col; j++){
            mat->data[i][j] = ((float)rand() / (float)RAND_MAX) * (.00001) ;
        }
    }
    return 0;
}
int initMatrix_Ones(matrix *mat){
    mat->data = (float **)calloc(mat->row, sizeof(float *));

    if(!mat->data){
        printf("Error allocating main data array!\n");
        return -1;
    }

    for(int i = 0; i < mat->row; i++) {
        mat->data[i] = (float *)calloc(mat->col, sizeof(float));
        if(!mat->data){
            printf("Error allocating sub array in data #%d!\n", i);
            return -1;
        }
    }

    for(int i=0; i < mat->row; i++){
        for(int j=0; j < mat->col; j++){
            mat->data[i][j] = 1.0;
        }
    }
    return 0;
}
int initMatrix_Data(matrix *mat, float dat[][3], int row, int col){
    mat->data = (float **)calloc(mat->row, sizeof(float *));
    if(!mat->data){
        printf("Error allocating main data array!\n");
        return -1;
    }

    for(int i = 0; i < mat->row; i++) {
        mat->data[i] = (float *)calloc(mat->col, sizeof(float));
        if(!mat->data){
            printf("Error allocating sub array in data #%d!\n", i);
            return -1;
        }
    }

    int min_row = (mat->row > row) ? row : mat->row;
    int min_col = (mat->col > col) ? col : mat->col;
    //printf("Min_row %d Min_col %d\n", min_row, min_col);

    for(int i=0; i < min_row; i++){
        for(int j=0; j < min_col; j++){
            mat->data[i][j] = dat[i][j];
        }
    }

    for(int i=0; i < mat->row; i++){
        for(int j=0; j < mat->col; j++){
            if( i >= min_row || j >= min_col ){
                mat->data[i][j] = 0.0;
            }
        }
    }

    return 0;
}
int initMatrix_Identity(matrix *mat){
    mat->data = (float **)calloc(mat->row, sizeof(float *));
    if(!mat->data){
        printf("Error allocating main data array!\n");
        return -1;
    }

    for(int i = 0; i < mat->row; i++) {
        mat->data[i] = (float *)calloc(mat->col, sizeof(float));
        if(!mat->data){
            printf("Error allocating sub array in data #%d!\n", i);
            return -1;
        }
    }

    for(int i=0; i < mat->row; i++){
        for(int j=0; j < mat->col; j++){
            mat->data[i][j] = (i == j) ? 1.0 : 0.0;
        }
    }

    return 0;
}

//Matrix Management Functions. ------------------------------------------------------------------------------------------------
int delMatrix(matrix *mat){
    for(int i=0; i < mat->row; i++){
        free(mat->data[i]);
    }
    free(mat->data);
    return 0;
}
int cloneMatrix(matrix *m1, matrix *m2){
    //Delete everything in m1...
    for(int i=0; i < m1->row; i++){
        free(m1->data[i]);
    }

    //Copy new row and column values from m2 to m1...
    m1->row = m2->row;
    m1->col = m2->col;

    //Remake m1 mem-architecture...
    m1->data = (float **)calloc(m1->row, sizeof(float *));
    for(int i = 0; i < m1->row; i++) {
        m1->data[i] = (float *)calloc(m1->col, sizeof(float));
    }

    //Copy data from m2 to m1...
    //Copy temporary data into new matrix...
    for(int i=0; i < m1->row; i++){
        for(int j=0; j < m1->col; j++){
            m1->data[i][j] = m2->data[i][j];
        }
    }

    return 0;
}

//Matrix Arithmetic Functions. ------------------------------------------------------------------------------------------------
matrix * addScalar(matrix *m1, float d2){
    for(int i=0; i < m1->row; i++){
        for(int j=0; j < m1->col; j++){
            m1->data[i][j] += d2;
        }
    }
    return m1;
}
matrix * addMatrix(matrix *m1, matrix *m2){
    int min_rows = (m1->row > m2->row) ? m2->row : m1->row;
    int min_cols = (m1->col > m2->col) ? m2->col : m1->col;

    for(int i=0; i < min_rows; i++){
        for(int j=0; j < min_cols; j++){
            m1->data[i][j] += m2->data[i][j];
        }
    }

    return m1;
}
matrix * subScalar(matrix *m1, float d2){
    for(int i=0; i < m1->row; i++){
        for(int j=0; j < m1->col; j++){
            m1->data[i][j] -= d2;
        }
    }
    return m1;
}
matrix * subMatrix(matrix *m1, matrix *m2){
    int min_rows = (m1->row > m2->row) ? m2->row : m1->row;
    int min_cols = (m1->col > m2->col) ? m2->col : m1->col;

    for(int i=0; i < min_rows; i++){
        for(int j=0; j < min_cols; j++){
            m1->data[i][j] -= m2->data[i][j];
        }
    }

    return m1;
}
matrix * mulScalar(matrix *m1, float d2){
    for(int i=0; i < m1->row; i++){
        for(int j=0; j < m1->col; j++){
            m1->data[i][j] *= d2;
        }
    }
    return m1;
}
matrix * dotMatrix(matrix *m1, matrix *m2){
    //printf("Rows - %d, Cols - %d\n", m2->row, m1->col);
    if (m1->col != m2->row){
        printf("Error (Dot Product): Matrix 1 cols must equal matrix 2 rows\n");
        printf("Matrix 1 = (%d, %d), Matrix 2 = (%d, %d)\n", m1->row, m1->col, m2->row, m2->col);
        return m1;
    }

    //Create tmp data with new mem-architecture.
    int tmp_row = m1->row;
    int tmp_col = m2->col;
    float **tmp = (float **)calloc(tmp_row, sizeof(float *));
    for(int i=0; i < tmp_row; i++){
        tmp[i] = (float *)calloc(tmp_col, sizeof(float));
    }

    //Perform calcs and assign data to new tmp matrix.
    for(int i=0; i < tmp_row; i++){
        for(int j=0; j < tmp_col; j++){
            float count = 0.0;

            for(int k=0; k < m1->col; k++){
                count += (m1->data[i][k] * m2->data[k][j]);
            }
            //printf("%.1f\n", count);
            tmp[i][j] = count;
        }
    }

    //Delete m1's old mem-architecture...
    for(int i=0; i < m1->row; i++){
        free(m1->data[i]);
    }

    //Make new mem-architecture...
    m1->row = tmp_row;
    m1->col = tmp_col;
    m1->data = (float **)calloc(m1->row, sizeof(float *));
    for(int i = 0; i < m1->row; i++) {
        m1->data[i] = (float *)calloc(m1->col, sizeof(float));
    }

    //Copy tmp data into new m1 matrix with new mem-architecture...
    for(int i=0; i < m1->row; i++){
        for(int j=0; j < m1->col; j++){
            m1->data[i][j] = tmp[i][j];
        }
    }

    //Free tmp data because we are all done...
    for(int i=0; i < tmp_row; i++){
        free(tmp[i]);
    }
    free(tmp);
    return m1;
}
matrix * elementMult(matrix *m1, matrix *m2){

    int min_rows = (m1->row > m2->row) ? m2->row : m1->row;
    int min_cols = (m1->col > m2->col) ? m2->col : m1->col;

    for(int i=0; i < min_rows; i++){
        for(int j=0; j < min_cols; j++){
            m1->data[i][j] *= m2->data[i][j];
        }
    }

    return m1;
}

//Matrix Debug Functions. ------------------------------------------------------------------------------------------------
void printMatrix(matrix *mat){

    for(int i=0; i < mat->row; i++){
        printf("| ");
        for(int j=0; j < mat->col; j++){
            printf("%.9f ", mat->data[i][j]);
        }
        printf("|\n");
    }

}

//Matrix Geometry Functions ------------------------------------------------------------------------------------------------
int transMatrix(matrix *mat){
    //Create temporary data...
    int tmp_row = mat->col;
    int tmp_col = mat->row;
    float **tmp = (float **)calloc(tmp_row, sizeof(float *));
    for(int i=0; i < tmp_row; i++){
        tmp[i] = (float *)calloc(tmp_col, sizeof(float));
    }

    //Copy old matrix data to temp data, with new mem-architecture.
    for(int i=0; i < tmp_row; i++){
        for(int j=0; j < tmp_col; j++){
            tmp[i][j] = mat->data[j][i];
        }
    }

    //Delete old memory architecture in 'matrix->data'...
    for(int i=0; i < mat->row; i++){
        free(mat->data[i]);
    }

    //Create new matrix with new mem-architecture...
    mat->row = tmp_row;
    mat->col = tmp_col;
    mat->data = (float **)calloc(mat->row, sizeof(float *));
    for(int i = 0; i < mat->row; i++) {
        mat->data[i] = (float *)calloc(mat->col, sizeof(float));
    }

    //Copy temporary data into new matrix...
    for(int i=0; i < mat->row; i++){
        for(int j=0; j < mat->col; j++){
            mat->data[i][j] = tmp[i][j];
        }
    }

    //Free up the mem used in the tmp variable...
    for(int i=0; i < tmp_row; i++){
        free(tmp[i]);
    }
    free(tmp);
    return 0;
}
int reshapeMatrix(matrix *m1, int n_rows, int n_cols){
    if( (n_rows * n_cols) != (m1->row * m1->col)){
        printf("Error (Reshape): new colmns * new rows must = old colmns * old rows\n");
        return -1;
    }

    //Create tmp array...
    float *tmp = calloc(m1->row * m1->col, sizeof(float));
    int tmp_count = 0;

    //Copy old matrix data to temp array...
    for(int i=0; i < m1->row; i++){
        for(int j=0; j < m1->col; j++){
            tmp[tmp_count] = m1->data[i][j];
            tmp_count++;
        }
    }

    //Delete old memory architecture in 'matrix->data'...
    for(int i=0; i < m1->row; i++){
        free(m1->data[i]);
    }

    //Reset count...
    //Overwrite matrix row and col parameters to the new ones.
    tmp_count = 0;
    m1->row = n_rows;
    m1->col = n_cols;

    //Create new matrix with new mem-architecture...
    m1->data = (float **)calloc(m1->row, sizeof(float *));
    for(int i = 0; i < m1->row; i++) {
        m1->data[i] = (float *)calloc(m1->col, sizeof(float));
    }

    //Copy temporary data into new matrix...
    for(int i=0; i < m1->row; i++){
        for(int j=0; j < m1->col; j++){
            m1->data[i][j] = tmp[tmp_count];
            tmp_count++;
        }
    }

    free(tmp);
    return 0;
}
int flatHorizMatrix(matrix *m1){
    reshapeMatrix(m1, 1, m1->row * m1-> col);
    return 0;
}
int flatVertMatrix(matrix *m1) {
    reshapeMatrix(m1, m1->row * m1-> col, 1);
    return 0;
}

matrix * vstackMat(matrix *m1, matrix *m2, int top_bot){

    matrix *output = malloc(sizeof(matrix) * 1);
    output->row = m1->row + m2->row;
    output->col = m1->col;
    initMatrix_Zeros(output);

    if (m1->col != m2->col){
        printf("Error - Can not concat vertically matrix's with different number of columns!!!\n");
        return output;
    }

    if (top_bot) {
        // Appending to the top!
        addMatrix(output, m2);

        // Add the other matrix manually...
        int k=0;
        for(int i = m2->row; i < output->row; i++){
            for(int j = 0; j < m1->col; j++){
                output->data[i][j] = m1->data[k][j];
            }
            k++;
        }

    }else{
        // Appending to the bottom!
        addMatrix(output, m1);

        // Add the other matrix manually...
        int k=0;
        for(int i = m1->row; i < output->row; i++){
            for(int j = 0; j < m2->col; j++){
                output->data[i][j] = m2->data[k][j];
            }
            k++;
        }
    }

    return output;
}
matrix * hstackMat(matrix *m1, matrix *m2, int lef_rit){

    matrix *output = malloc(sizeof(matrix) * 1);
    output->row = m1->row;
    output->col = m1->col + m2->col;
    initMatrix_Zeros(output);

    if (m1->row != m2->row){
        printf("Error - Can not concat horizontally matrix's with different number of rows!!!\n");
        return output;
    }

    if (lef_rit) {
        // Appending to the left!
        addMatrix(output, m2);

        // Add the other matrix manually...
        for(int i = 0; i < m1->row; i++){

            int k=0;
            for(int j = m2->col; j < output->col; j++){
                output->data[i][j] = m1->data[i][k];
                k++;
            }
        }

    }else{
        // Appending to the right!
        addMatrix(output, m1);

        // Add the other matrix manually...
        for(int i = 0; i < m2->row; i++){

            int k=0;
            for(int j = m1->col; j < output->col; j++){
                output->data[i][j] = m2->data[i][k];
                k++;
            }
        }
    }

    return output;
}

int popRows(matrix *m1, int num_rows, int top_bot){
    // All rows get pushed up!!
    matrix tmp;
    tmp.row = m1->row - num_rows;
    tmp.col = m1->col;
    initMatrix_Zeros(&tmp);

    if (num_rows >= m1->row){
        printf("Error (PopRows) - Can not pop more rows than the matrix has, or all the rows out of the matrix.\n");
        return 1;
    }else if (num_rows <= 0){
        printf("Error (PopRows) - Can not pop 0 or negative rows.\n");
        return 1;
    }

    if (top_bot){
        // Popping from the top!!
        int k =0;
        for(int i = num_rows; i < m1->row; i++){
            for(int j = 0; j < m1->col; j++){
                tmp.data[k][j] = m1->data[i][j];
            }
            k++;
        }
    }else{
        // Popping from the bottom!!
        int k =0;
        for(int i = 0; i < (m1->row - num_rows); i++){
            for(int j = 0; j < m1->col; j++){
                tmp.data[k][j] = m1->data[i][j];
            }
            k++;
        }
    }

    cloneMatrix(m1, &tmp);
    delMatrix(&tmp);
    return 0;
}
int popCols(matrix *m1, int num_cols, int lef_rit){

    matrix tmp;
    tmp.row = m1->row;
    tmp.col = m1->col - num_cols;
    initMatrix_Zeros(&tmp);

    if (num_cols >= m1->col){
        printf("Error (PopCols) - Can not pop more cols than the matrix has, or all the cols out of the matrix.\n");
        return 1;
    }else if (num_cols <= 0){
        printf("Error (PopCols) - Can not pop 0 or negative cols.\n");
        return 1;
    }

    if(lef_rit){
        // Popping from the left!
        for(int i = 0; i < m1->row; i++){
            int k =0;
            for(int j = num_cols; j < m1->col; j++){
                tmp.data[i][k] = m1->data[i][j];
                k++;
            }
        }
    }else{
        // Popping from the right!
        for(int i = 0; i < m1->row; i++){
            int k =0;
            for(int j = 0; j < (m1->col - num_cols); j++){
                tmp.data[i][k] = m1->data[i][j];
                k++;
            }
        }
    }

    cloneMatrix(m1, &tmp);
    delMatrix(&tmp);

    return 0;
}

// Add definition for these!
int shiftRows(matrix *m1, int num_shift, int top_bot){

    if(popRows(m1, num_shift, top_bot)){
        return 1;
    }

    matrix zeros;
    zeros.row = num_shift;
    zeros.col = m1->col;
    initMatrix_Zeros(&zeros);

    //Used to catch matrix so we can clean up later with delete.
    matrix *final = vstackMat(m1, &zeros, !top_bot);
    cloneMatrix(m1, final);

    delMatrix(final);
    return 0;
}
int shiftCols(matrix *m1, int num_shift, int lef_rit){
    if(popCols(m1, num_shift, lef_rit)){
        return 1;
    }

    matrix zeros;
    zeros.row = m1->row;
    zeros.col = num_shift;
    initMatrix_Zeros(&zeros);

    //Used to catch matrix so we can clean up later with delete.
    matrix *final = hstackMat(m1, &zeros, !lef_rit);

    cloneMatrix(m1, final);

    delMatrix(final);
    return 0;
}
