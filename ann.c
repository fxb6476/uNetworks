#include <stdio.h>
#include <string.h>
#include <time.h>
#include <math.h>
#include <stdlib.h>
#include "ann.h"

//Init neuron matrix by putting random weights into network neurons.
int initANN(FF_ANN *net){
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

    //Randomly assign weight values 0 - 1 for each neuron weight.
    //Also assigns bias of 0.0 for now...
    for(int i=0; i < net->n_layers; i++){
        for(int j=0; j < net->layer_sizes[i]; j++){
            net->neuron_matrix[i][j].weight = rand()/(float)RAND_MAX;
            net->neuron_matrix[i][j].bias = 0.0;
        }
    }

    return 0;
}

//Delete network by freeing matrix and array for layer size.
int delANN(FF_ANN *net){
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
    return 0;
} /// NOT DONE YET!!!

//Prints the net
void printANN(FF_ANN *net){
    for(int i=0; i < net->n_layers; i++) {
        printf("| ");
        for (int j = 0; j < net->layer_sizes[i]; j++) {
            printf("[%.2f, %.2f] ", net->neuron_matrix[i][j].weight, net->neuron_matrix[i][j].bias);
        }
        printf("|\n");
    }
}