/*
 * Felix Blanco
 * - Defines neron structure, network structure, functions, initializers, etc.
 * - ToDO
 * 1) Define new functions.
 *    a) Cost Functions - crossEntroyLoss, derivativeCrossEntropy, squaredError, derivativeSquaredError
 *    b) Activation Functions - activateSoftMax, derivativeSoftMax
 *    c) Redefine how back prop works to better allow for swapping in and out activation and cost functions!
 *         -> Perhaps even look into passing cost and activation functions by reference... ohhhh snazzy!!
 *    d) Update Feed Forward function to better allow for swapping in and out activations.
 *         -> Perhaps even look into passing cost and activation functions by reference... ohhhh snazzy!!
 */


#pragma once
#ifndef ann_h
#include "matrix.h"

typedef struct{
    int n_layers;
    int layer_sizes[100];
    matrix *bias;
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
int backProp_ANN(FC_ANN *net, matrix *guessed_outs, float *output, int output_size, float learning_rate);

// Activation Functions. ------------------------------------------------------------------------------------------------

// Good for shallow networks. Not good for deep networks.
// Learning with sigmoid can take more time than Relu.
// Use this for output layer activation when trying to estimate a linear function.
// This can be used for hidden layers even if you are doing classification.
void activateSigmoid(matrix *m1);
void derivativeSigmoid(matrix *m1);

// Good for deep networks.
// Often time switching from sigmoid to Relu requires upping number of hidden layers, and decreasing learning rate!
// Use this for output layer activation when trying to estimate a linear function.
// This can be used for hidden layers even if you are doing classification.
void activateRelu(matrix *m1);
void derivativeRelu(matrix *m1);

// Used typically on only the output layer of your network!
// Must be used in output layer when performing multi-class classification.
// Typically, when using softmax() for output layer activation you must use some sort of probabilistic Cost function.
// Appropriate cost functions are Cross Entropy Loss, Kullback-leibler, etc.
void activateSoftMax(matrix *m1);
void derivativeSoftMax(matrix *m1);

// Cost/Loss Functions. ------------------------------------------------------------------------------------------------

// ---------- Squared Error ----------
// * This error is typically used when doing regression or linear approximation with ur network!
// (y - guessed) ^ 2
matrix * squaredError(matrix *guessed, matrix *real);
// dC/dA = Change in Cost / Change in guess = 2*(y - guessed)
matrix * derivativeSquaredError(matrix *guessed, matrix *real);

// ---------- Cross Entropy Loss ----------
// * Used when network output is a probability distribution.
// * IE - When your network uses something link SoftMax() for the output layer activation.
// -> Loss = - SUM(y_node * log(guess_probability_node))
// -> Node = I mean each output neuron.
matrix * crossEntroyLoss(matrix *guessed, matrix *label);
// After doing math out...
// change in LOSS = probability_of_guess - label
matrix * derivativeCrossEntropy(matrix *guessed, matrix *label);


//Debug Network Functions. ------------------------------------------------------------------------------------------------
void printANN(FC_ANN *net);

#endif