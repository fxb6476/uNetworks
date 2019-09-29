/*
 * Felix Blanco
 * - Defines neron structure, network structure, functions, initializers, etc.
 * - ToDO
 * 1)
 */


#pragma once
#ifndef ann_h

typedef struct{
    float weight;
    float bias;
}neuron;

typedef struct{
    int n_layers;
    int *layer_sizes;
    neuron **neuron_matrix;
}FF_ANN;

//Init neuron matrix by putting random weights into network neurons.
int initANN(FF_ANN *net);

//Delete network by freeing matrix and array for layer size.
int delANN(FF_ANN *net);

//Train network by feeding data through the network, and use output error to change weights.
//This uses the logistic activation function = 1/(1+e^(-z))...
//The cost function will be squared error (target - estimated output)^2
int trainANN(FF_ANN *net, float *input, float *output);

#endif