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

    matrix *images = grabImages("./mnist_data/train-images-idx3-ubyte", 0, 1000, 28, 28);
    matrix *labels = grabLabels("./mnist_data/train-labels-idx1-ubyte", 0, 1000);

    //reshapeMatrix(&images[8], 28, 28);
    //printMatrix(&images[8 ]);
    //printf("Label - %.1f\n", labels[0].data[0][8]);

    printIdx("./mnist_data/train-images-idx3-ubyte");
    printIdx("./mnist_data/train-labels-idx1-ubyte");


    FC_ANN ann1;
    ann1.n_layers = 5;
    ann1.layer_sizes[0] = 784;
    ann1.layer_sizes[1] = 300;
    ann1.layer_sizes[2] = 150;
    ann1.layer_sizes[3] = 75;
    ann1.layer_sizes[4] = 10;

    if(initANN(&ann1)) return -1;
    printANN(&ann1);

    matrix *outputs;

    for (int rounds = 0; rounds < 50; rounds++){

        printf("------------------------- Round #%d -------------------------\n", rounds);

        for(int i = 0; i < 1000; i++){

            printf("[+] -------------------- Sample #%d output...\n", i+1);

            outputs = feedANN(&ann1, images[i].data[0], 784);

            //for(int i = 0; i < ann1.n_layers; i++){
                printf("Output #%d\n", ann1.n_layers-1);
                printMatrix(&outputs[ann1.n_layers-1]);
                printf("\n");
            //}

            printf("----- Real output!\n");
            printMatrix(&labels[i]);

            backProp_ANN(&ann1, outputs, labels[i].data[0], 10, 1.0);

            for(int i=0; i < ann1.n_layers; i++){
                delMatrix(&outputs[i]);
            }

        }
    }

    free(outputs);

    delANN(&ann1);

    printf("Good bye!\n");

    return 0;
}