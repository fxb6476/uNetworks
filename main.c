#include <stdio.h>
#include <string.h>
#include <math.h>
#include <stdlib.h>
#include "matrix.h"
#include "ann.h"

int main(){

    /* UNCOMMENT THIS TO TESTS THE MATRIX's
    // A Volume will be an array of matricies, or pointer to mem block of structs
    // Do dynamic allocation
    int vol_size = 6;
    matrix *image = malloc(vol_size * sizeof(matrix));

    for(int i=0; i < vol_size; i++) {
        image[i].col = 3;
        image[i].row = 3;
        initMatrix_Identity(&image[i]);

        printf("Printing matrix %d of volume...\n", i);
        printMatrix(&image[i]);
        printf("\n");
        delMatrix(&image[i]);
    }

    float data[][3] = {{1.0, 2.0, 3.0},
                       {4.0, 5.0, 6.0},
                       {7.0, 8.0, 9.0}};

    matrix m4 = {3, 3};
    initMatrix_Data(&m4, data, 3, 3);

    matrix m5 = {3, 3};
    initMatrix_Identity(&m5);

    dotMatrix(&m4, &m5);
    printMatrix(&m4);

    flatHorizMatrix(&m4);
    cloneMatrix(&m5, &m4);
    printMatrix(&m4);
    printMatrix(&m5);

    //Clean up...
    delMatrix(&m4);
    delMatrix(&m5);
    */

    // TESTING THE FF_ANN
    FF_ANN ann1 = {4, {10, 3, 2, 1}};

    if(initANN(&ann1)) return -1;
    printANN(&ann1);
    delANN(&ann1);

    return 0;
}