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
    FC_ANN ann1 = {4, {5, 4, 3, 3}};
    float data[] = {1.43, 8.11, 9.999, 10.1234, 22.2222};
    float out_data[] = {1.43, 2.22, 1.11};

    if(initANN(&ann1)) return -1;
    printANN(&ann1);

    matrix *outputs;
    outputs = feedANN(&ann1, data, 5);

    for(int i=0; i < ann1.n_layers; i++){
        printf("Printing Output of Layer #%d\n", i);
        printMatrix(&outputs[i]);
        printf("\n");
    }

    backProp_ANN(&ann1, outputs, out_data, 3);

    for(int i=0; i < ann1.n_layers; i++){
        delMatrix(&outputs[i]);
    }

    free(outputs);

    delANN(&ann1);

    return 0;
}