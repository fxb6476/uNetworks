#include <stdio.h>
#include <string.h>
#include <math.h>
#include <stdlib.h>
#include "matrix.h"
#include "ann.h"

int main(){

    // TESTING THE FF_ANN
    FC_ANN ann1 = {3, {2, 3, 1}};
    float in_data[][2] = {{1.0, 1.0},
                          {1.0, 0.0},
                          {0.0, 1.0},
                          {0.0, 0.0}};
    float out_data[][1] = {{0.0},
                           {1.0},
                           {1.0},
                           {1.0}};

    if(initANN(&ann1)) return -1;
    printANN(&ann1);

    matrix *outputs;

    for (int rounds = 0; rounds < 3000; rounds++){

        printf("------------------------- Round #%d -------------------------\n", rounds);

        for(int i = 0; i < 4; i++){

            printf("[+] -------------------- Sample #%d output...\n", i+1);

            outputs = feedANN(&ann1, in_data[i], 2);

            //for(int i = 0; i < ann1.n_layers; i++){
                printf("Output #%d\n", ann1.n_layers-1);
                printMatrix(&outputs[ann1.n_layers-1]);
                printf("\n");
            //}

            backProp_ANN(&ann1, outputs, out_data[i], 1, 1.0);

            for(int i=0; i < ann1.n_layers; i++){
                delMatrix(&outputs[i]);
            }

        }
    }

    printANN(&ann1);

    free(outputs);

    delANN(&ann1);

    printf("Good bye!\n");
    return 0;
}