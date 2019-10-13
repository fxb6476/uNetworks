#include <stdio.h>
#include <string.h>
#include <time.h>
#include <math.h>
#include <stdlib.h>
#include "ann.h"

//Init neuron matrix by putting random weights into network neurons.
int initANN(FF_ANN *net){
    if(net->layer_sizes[0] <= 0){
        printf("Error (initANN) - You cannot have an input layer of 0 or less!\n");
        return 1;
    }

    if(net->layer_sizes[net->n_layers-1] <= 0){
        printf("Error (initANN) - You cannot have an output layer of 0 or less!\n");
        return 1;
    }

    if(net->n_layers > 100){
        printf("Error (initANN) - You can not have more than 100 layers, its just not supported!\n");
        return 1;
    }

    //Init random number generator. Always generates with different seed.
    srand((long)time(NULL));

    //Checking if layers are less than a predefined value.
    for(int i=0; i < net->n_layers; i++){
        //printf("Size of layer %d is %d...\n", i+1, net->layer_sizes[i]);
        if (net->layer_sizes[i] == 0){
            printf("ERROR (Layer size) - Layer %d is 0, layers can not be size 0!\n", i+1);
            return 1;
        }
    }

    //Create initial matrix of neurons...
    //Architecture is defined by number of layers, including input and output & the size of each layer (count of neurons in each layer).
    net->neuron_matrix = (neuron **)malloc(net->n_layers * sizeof(neuron *));
    for(int i=0; i < net->n_layers; i++){
        net->neuron_matrix[i] = (neuron *)malloc(net->layer_sizes[i] * sizeof(neuron));
    }

    //Create dynamic array with number of weights for each neron....
    //Randomly assign weight values 0 - 1 for each neuron weight.
    //Also assigns bias of 0.0 for now...
    //The weight pointer of each neuron, in the input layer, will point to NULL, thus can be free()'ed
    for(int j=0; j < net->layer_sizes[0]; j++){
        net->neuron_matrix[0][j].weights = NULL;
    }

    for(int i=1; i < net->n_layers; i++){
        //This selects the layer ^
        for(int j=0; j < net->layer_sizes[i]; j++){
                net->neuron_matrix[i][j].weights = (float *)malloc( net->layer_sizes[i-1] * sizeof(float));

                for(int k = 0; k < net->layer_sizes[i-1]; k++){
                    net->neuron_matrix[i][j].weights[k] = rand()/(float)RAND_MAX;
                }

                net->neuron_matrix[i][j].bias = 0.0;

        }
    }

    return 0;
}

//Delete network by freeing matrix and array for layer size.
int delANN(FF_ANN *net){
    //Delete all weights for each neuron...
    for(int i=0; i < net->n_layers; i++) {
        for (int j = 0; j < net->layer_sizes[i]; j++) {
            free(net->neuron_matrix[i][j].weights);
        }
    }

    for(int i=0; i < net->n_layers; i++){
        free(net->neuron_matrix[i]);
    }
    free(net->neuron_matrix);
    return 0;
}

//Train network by feeding data through the network, and use output error to change weights.
//This uses the logistic activation function = 1/(1+e^(-z))...
//The cost function will be squared error (target - estimated output)^2
int trainANN(FF_ANN *net, float *input, float *output){
    //Output of each neuron will be -> sum of each input times its respective weight added together
    return 0;
} /// NOT DONE YET!!!

//Prints the net
void printANN(FF_ANN *net){
    printf("------------ Network Topology ------------\n");
    printf(" * Input Size        = %d\n", net->layer_sizes[0]);
    printf(" * Output Size       = %d\n", net->layer_sizes[net->n_layers-1]);
    printf(" * Num Hidden Layers = %d\n", net->n_layers);
    printf("------------------------------------------\n");
    printf("------------------------------------------\n\n");
    printf("------------ Network Weights -------------\n");
    for(int i=1; i < net->n_layers; i++) {
        printf("------------ Hidden Layer #%d ------------ \n", i);
        for (int j = 0; j < net->layer_sizes[i]; j++) {

            printf("Neuron #%d --> | ", j+1);
            for(int k=0; k < net->layer_sizes[i-1]; k++){
                printf("%.4f ", net->neuron_matrix[i][j].weights[k]);
            }
            printf("| Bias = %.4f |\n", net->neuron_matrix[i][j].bias);
        }
        printf("\n");
    }
}