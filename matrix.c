#include <stdio.h>
#include <string.h>
#include <math.h>
#include <stdlib.h>
#include "matrix.h"

int initMatrix_Zeros(matrix *mat){
    mat->data = malloc(mat->col * mat->row * mat->data_size);
    for(int i = 0; i < mat->row; i++) {
        for (int j = 0; j < mat->col; j++) {
            switch (mat->data_type) {
                case 0:
                    *((int *) (mat->data + i * mat->col + j)) = 0;
                    break;
                case 1:
                    *((double *) (mat->data + i * mat->col + j)) = 0.0;
                    break;
                case 2:
                    *((float *) (mat->data + i * mat->col + j)) = 0.0;
                    break;
                case 3:
                    *((char *) (mat->data + i * mat->col + j)) = '0';
                    break;
                case 4:
                    *((long *) (mat->data + i * mat->col + j)) = 0.0;
                    break;
                default:
                    *((int *) (mat->data + i * mat->col + j)) = 0;
                    break;
            }
        }
    }
    return 0;
}
int delMatrix(matrix *mat){
    free(mat->data);
    return 0;
}
void printMatrix(matrix *mat){
    for(int i=0; i < mat->row; i++){
        printf("| ");
        for(int j=0; j < mat->col; j++){
            switch (mat->data_type) {
                case 0:
                    printf("%d ", *((int *) (mat->data + i * mat->col + j)));
                    break;
                case 1:
                    printf("%.1f ", *((double *) (mat->data + i * mat->col + j)));
                    break;
                case 2:
                    printf("%.4f ", *((float *) (mat->data + i * mat->col + j)));
                    break;
                case 3:
                    printf("%c ", *((char *) (mat->data + i * mat->col + j)));
                    break;
                case 4:
                    printf("%ld ", *((long *) (mat->data + i * mat->col + j)));
                    break;
                default:
                    printf("%d ", *((int *) (mat->data + i * mat->col + j)));
                    break;
            }
        }
        printf("|\n");
    }
}