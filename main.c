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

    matrix *images = grabImages("./mnist_data/train-images-idx3-ubyte", 0, 5000, 28, 28);
    matrix *labels = grabLabels("./mnist_data/train-labels-idx1-ubyte", 0, 5000);

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

    // Training network!!
    for (int rounds = 0; rounds < 50; rounds++){

        printf("------------------------- Round #%d -------------------------\n", rounds);

        float percentage = 0.0;

        for(int i = 0; i < 5000; i++){

            outputs = feedANN(&ann1, images[i].data[0], 784);

            float test_error = 0.0;

            for(int j=0; j < 10; j++){
                //printf("Prediction = %.4f, Actual = %.4f\n", outputs[ann1.n_layers-1].data[0][j], labels[i].data[0][j]);
                test_error += (outputs[ann1.n_layers-1].data[0][j] - labels[i].data[0][j]);
            }
            //printf("%.4f\n", test_error);
            percentage += test_error;

            backProp_ANN(&ann1, outputs, labels[i].data[0], 10, 0.00001);

            for(int i=0; i < ann1.n_layers; i++){
                delMatrix(&outputs[i]);
            }

        }
        percentage = percentage / 5000;

        printf("Average round error - %.4f\n", percentage * 100);
    }

    // Clean up old matrix's
    for(int i=0; i < 5000; i++){
        delMatrix(&images[i]);
        delMatrix(&labels[i]);
    }

    images = grabImages("./mnist_data/train-images-idx3-ubyte", 5000, 10, 28, 28);
    labels = grabLabels("./mnist_data/train-labels-idx1-ubyte", 5000, 10);

    // Testing network!!
    printf("------------------------- TIME TO TEST THE NETWORK!! -------------------------\n");

    for(int i = 0; i < 10; i++){

        printf("Testing image number %d!!!!\n", i+1);

        outputs = feedANN(&ann1, images[i].data[0], 784);

        printf("Guessed Data!! \n");
        printMatrix(&outputs[ann1.n_layers-1]);

        printf("Real Data!!!! \n");
        printMatrix(&labels[i]);

        printf("\n");

        for(int i=0; i < ann1.n_layers; i++){
            delMatrix(&outputs[i]);
        }

    }

    free(outputs);

    delANN(&ann1);

    printf("Good bye!\n");

    return 0;
}