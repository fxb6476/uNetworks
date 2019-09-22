#include <stdio.h>
#include <string.h>
#include <math.h>
#include <stdlib.h>
#include "matrix.h"

int main(){
    matrix m1 = {6, 4, sizeof(int), 0};
    initMatrix_Zeros(&m1);
    printMatrix(&m1);
    delMatrix(&m1);
    return 0;
}