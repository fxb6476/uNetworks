#include <stdio.h>
#include <string.h>
#include <math.h>
#include <stdlib.h>
#include "matrix.h"

int main(){

    matrix m1 = {2, 4};
    matrix m2 = {3, 7};
    matrix m3 = {2, 2};

    matrix image[3] = {m1, m2, m3};

    for(int i=0; i < 3; i++){
        initMatrix_Zeros(&image[i]);
        printMatrix(&image[i]);
        delMatrix(&image[i]);
    }

    return 0;
}