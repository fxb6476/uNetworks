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

//Feeds data through ANN and returns matrix's of outputs for each layer.
matrix * feedANN(FC_ANN *net, float *input, int input_size);

//Back propagation of error through network layers...
//Using the chain rule method, things are going to get messy :/
int backProp_ANN(FC_ANN *net, matrix *guessed_outs, float *output, int output_size);

void activationFunc(matrix *m1);
void der_of_activ_func(matrix *m1);

//Debugging network printer...
void printANN(FC_ANN *net);

#endif