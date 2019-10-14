/*
 * Felix Blanco
 * - Defines neron structure, network structure, functions, initializers, etc.
 * - ToDO
 * 1)
 */


#pragma once
#ifndef ann_h
#include "matrix.h"

typedef struct{
    int n_layers;
    int layer_sizes[100];
    float *layer_biases;
    matrix *weights_matrix;
}FC_ANN;

//Init neuron matrix by putting random weights into network neurons.
int initANN(FC_ANN *net);

//Delete network by freeing matrix and array for layer size.
int delANN(FC_ANN *net);

//Train network by feeding data through the network, and use output error to change weights.
//This uses the logistic activation function = 1/(1+e^(-z))...
//The cost function will be squared error (target - estimated output)^2

//Feeds data through ANN and returns matrix's of outputs for each layer.
matrix * feedANN(FC_ANN *net, float *input, int input_size);

void activationFunc(matrix *m1);

//Debugging network printer...
void printANN(FC_ANN *net);

#endif