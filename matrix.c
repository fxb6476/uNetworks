#include <stdio.h>
#include <string.h>
#include <math.h>
#include <stdlib.h>
#include "matrix.h"

int initMatrix_Zeros(matrix *mat){
    mat->data = (float **)malloc(mat->row * sizeof(float *));
    for(int i = 0; i < mat->row; i++) {
        mat->data[i] = (float *)malloc(mat->col * sizeof(float));
    }

    for(int i=0; i < mat->row; i++){
        for(int j=0; j < mat->col; j++){
            mat->data[i][j] = 0.0;
        }
    }
    return 0;
}
int initMatrix_Data(matrix *mat, float dat[][3], int row, int col){
    mat->data = (float **)malloc(mat->row * sizeof(float *));
    for(int i = 0; i < mat->row; i++) {
        mat->data[i] = (float *)malloc(mat->col * sizeof(float));
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
    mat->data = (float **)malloc(mat->row * sizeof(float *));
    for(int i = 0; i < mat->row; i++) {
        mat->data[i] = (float *)malloc(mat->col * sizeof(float));
    }

    for(int i=0; i < mat->row; i++){
        for(int j=0; j < mat->col; j++){
            mat->data[i][j] = (i == j) ? 1.0 : 0.0;
        }
    }

    return 0;
}

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
    m1->data = (float **)malloc(m1->row * sizeof(float *));
    for(int i = 0; i < m1->row; i++) {
        m1->data[i] = (float *)malloc(m1->col * sizeof(float));
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

int addScalar(matrix *m1, float d2){
    for(int i=0; i < m1->row; i++){
        for(int j=0; j < m1->col; j++){
            m1->data[i][j] += d2;
        }
    }
    return 0;
}
int addMatrix(matrix *m1, matrix *m2){
    int min_rows = (m1->row > m2->row) ? m2->row : m1->row;
    int min_cols = (m1->col > m2->col) ? m2->col : m1->col;

    for(int i=0; i < min_rows; i++){
        for(int j=0; j < min_cols; j++){
            m1->data[i][j] += m2->data[i][j];
        }
    }

    return 0;
}
int subScalar(matrix *m1, float d2){
    for(int i=0; i < m1->row; i++){
        for(int j=0; j < m1->col; j++){
            m1->data[i][j] -= d2;
        }
    }
    return 0;
}
int subMatrix(matrix *m1, matrix *m2){
    int min_rows = (m1->row > m2->row) ? m2->row : m1->row;
    int min_cols = (m1->col > m2->col) ? m2->col : m1->col;

    for(int i=0; i < min_rows; i++){
        for(int j=0; j < min_cols; j++){
            m1->data[i][j] -= m2->data[i][j];
        }
    }

    return 0;
}
int mulScalar(matrix *m1, float d2){
    for(int i=0; i < m1->row; i++){
        for(int j=0; j < m1->col; j++){
            m1->data[i][j] *= d2;
        }
    }
    return 0;
}
int dotMatrix(matrix *m1, matrix *m2){
    //printf("Rows - %d, Cols - %d\n", m2->row, m1->col);
    if (m1->col != m2->row){
        printf("Error (Dot Product): Matrix 1 cols must equal matrix 2 rows\n");
        return -1;
    }

    //Create tmp data with new mem-architecture.
    int tmp_row = m1->row;
    int tmp_col = m2->col;
    float **tmp = (float **)malloc(tmp_row * sizeof(float *));
    for(int i=0; i < tmp_row; i++){
        tmp[i] = (float *)malloc(tmp_col * sizeof(float));
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
    m1->data = (float **)malloc(m1->row * sizeof(float *));
    for(int i = 0; i < m1->row; i++) {
        m1->data[i] = (float *)malloc(m1->col * sizeof(float));
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
    return 0;
}

int transMatrix(matrix *mat){
    //Create temporary data...
    int tmp_row = mat->col;
    int tmp_col = mat->row;
    float **tmp = (float **)malloc(tmp_row * sizeof(float *));
    for(int i=0; i < tmp_row; i++){
        tmp[i] = (float *)malloc(tmp_col * sizeof(float));
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
    mat->data = (float **)malloc(mat->row * sizeof(float *));
    for(int i = 0; i < mat->row; i++) {
        mat->data[i] = (float *)malloc(mat->col * sizeof(float));
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

void printMatrix(matrix *mat){
    for(int i=0; i < mat->row; i++){
        printf("| ");
        for(int j=0; j < mat->col; j++){
            printf("%.4f ", mat->data[i][j]);
        }
        printf("|\n");
    }
}
int reshapeMatrix(matrix *m1, int n_rows, int n_cols){
    if( (n_rows * n_cols) != (m1->row * m1->col)){
        printf("Error (Reshape): new colmns * new rows must = old colmns * old rows\n");
        return -1;
    }

    //Create tmp array...
    float *tmp = malloc(m1->row * m1->col * sizeof(float));
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
    m1->data = (float **)malloc(m1->row * sizeof(float *));
    for(int i = 0; i < m1->row; i++) {
        m1->data[i] = (float *)malloc(m1->col * sizeof(float));
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