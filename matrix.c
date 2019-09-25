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
int delMatrix(matrix *mat){
    for(int i=0; i < mat->row; i++){
        free(mat->data[i]);
    }
    free(mat->data);
    return 0;
}
int cloneMatrix(matrix *m1, matrix *m2){

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