#include <stdio.h>
#include <string.h>
#include <math.h>
#include <stdlib.h>
#include "matrix.h"
#include "ann.h"
#include "mnist.h"

int main(){

    // TESTING FC_ANN
    // This will try to teach the network to identify two clases.
    // Class 1 = everything above the identity line y = x.
    // Class 0 = everything bellow the identity line.

    matrix *images = grabImages("./mnist_data/train-images-idx3-ubyte", 0, 10, 28, 28);
    matrix *labels = grabLabels("./mnist_data/train-labels-idx1-ubyte", 0, 10);
    printf("Got here\n");
    reshapeMatrix(&images[0], 28, 28);
    printMatrix(&images[0]);
    printf("Label - %.1f\n", labels[0].data[0][0]);

    printIdx("./mnist_data/train-images-idx3-ubyte");
    printIdx("./mnist_data/train-labels-idx1-ubyte");

    /*
    FC_ANN ann1 = {3, {2, 3, 1}};
    float in_data[][2] = {{1.0, 2.0},
                          {6.0, 10.0},
                          {5.0, 8.0},
                          {3.0, 40.0},
                          {23.0, 6.0},
                          {4.0, 1.0},
                          {10.0, 8.0},
                          {2.0, 1.0}};
    float out_data[][1] = {{1.0},
                           {1.0},
                           {1.0},
                           {1.0},
                           {0.0},
                           {0.0},
                           {0.0},
                           {0.0}};

    if(initANN(&ann1)) return -1;
    printANN(&ann1);

    matrix *outputs;

    for (int rounds = 0; rounds < 1000; rounds++){

        printf("------------------------- Round #%d -------------------------\n", rounds);

        for(int i = 0; i < 8; i++){

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

    float new_data[] = {1.0, 100.0};
    printf("\nTesting on data it has never seen lol %.3f, %.3f...\n", new_data[0], new_data[1]);

    outputs = feedANN(&ann1, new_data, 2);

    printf("Predicted class should be 1.0\n");
    printf("Networks prediction...\n");
    printMatrix(&outputs[ann1.n_layers-1]);

    for(int i=0; i < ann1.n_layers; i++){
        delMatrix(&outputs[i]);
    }

    free(outputs);

    delANN(&ann1);

    printf("Good bye!\n");
     */
    return 0;
}