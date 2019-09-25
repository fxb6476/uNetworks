#include <stdio.h>
#include <string.h>
#include <math.h>
#include <stdlib.h>
#include "matrix.h"

int main(){

    matrix m1 = {2, 4};
    matrix m2 = {3, 7};
    matrix m3 = {2, 2};

    // A Volume will be an array of matricies.
    matrix image[3] = {m1, m2, m3};

    float data[][3] = {{1.0, 0.0, 0.0},
                       {0.0, 1.0, 0.0},
                       {0.0, 0.0, 1.0}};

    matrix m4 = {5, 5};
    matrix m5 = {4, 4};

    initMatrix_Data(&m4, data, 3, 3);
    initMatrix_Identity(&m5);

    printMatrix(&m5);

    for(int i=0; i < 3; i++){
        initMatrix_Zeros(&image[i]);
        //printMatrix(&image[i]);
        delMatrix(&image[i]);
    }

    delMatrix(&m4);

    return 0;
}