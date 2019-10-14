#include <stdio.h>
#include <string.h>
#include <math.h>
#include <stdlib.h>
#include "ann.h"

//Init neuron matrix by putting random weights into network neurons.
int initANN(FC_ANN *net){
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


    //Checking if layers are less than a predefined value.
    for(int i=0; i < net->n_layers; i++){
        //printf("Size of layer %d is %d...\n", i+1, net->layer_sizes[i]);
        if (net->layer_sizes[i] == 0){
            printf("ERROR (Layer size) - Layer %d is 0, layers can not be size 0!\n", i+1);
            return 1;
        }
    }

    //Create pointers to matrix's, each layer is just a matrix of weights...
    net->weights_matrix = (matrix *)malloc(net->n_layers * sizeof(matrix *));

    //Creating first matrix... Input layer.
    net->weights_matrix[0].row = net->layer_sizes[0];
    net->weights_matrix[0].col = 1;
    initMatrix_Ones(&net->weights_matrix[0]);

    for(int i=1; i < net->n_layers; i++){
        net->weights_matrix[i].row = net->layer_sizes[i-1];
        net->weights_matrix[i].col = net->layer_sizes[i];
        initMatrix_Random(&net->weights_matrix[i]);
    }

    return 0;
}

//Delete network by freeing matrix and array for layer size.
int delANN(FC_ANN *net){
    //Delete each matrix we are pointing to...
    for(int i=0; i < net->n_layers; i++){
        delMatrix(&net->weights_matrix[i]);
    }

    //Free out actual pointer.
    free(net->weights_matrix);
    return 0;
}

//Train network by feeding data through the network, and use output error to change weights.
//This uses the logistic activation function = 1/(1+e^(-z))...
//The cost function will be squared error (target - estimated output)^2

//Feeds data through ANN and returns matrix's of outputs for each layer.
matrix * feedANN(FC_ANN *net, float *input, int input_size){

    if ( input_size != net->layer_sizes[0] ){
        printf("Error (Feed ANN) - Input data must be the same size as layer 1!\n");
        //ToDo
        // Need to throw an error here instead of just letting this slide!!
    }

    printf("\nFeeding Data Through Network.... Stand By!!\n\n");

    matrix *tmp_mat_ptr = (matrix *)malloc(net->n_layers * sizeof(matrix *));
    tmp_mat_ptr[0].col = net->layer_sizes[0]; tmp_mat_ptr[0].row = 1;
    initMatrix_Zeros(&tmp_mat_ptr[0]);

    for(int i=0; i < tmp_mat_ptr[0].col; i++){
        tmp_mat_ptr[0].data[0][i] = input[i];
    }

    //printf("Printing Output of Layer #%d\n", 0);
    //printMatrix(&tmp_mat_ptr[0]);
    //printf("\n");

    for(int i=1; i < net->n_layers; i++){
        matrix tmp_mat = {1, 1};
        initMatrix_Ones(&tmp_mat);

        tmp_mat_ptr[i].col = 1; tmp_mat_ptr[i].row = 1;
        initMatrix_Ones(&tmp_mat_ptr[i]);

        cloneMatrix(&tmp_mat, &tmp_mat_ptr[i-1]);

        dotMatrix(&tmp_mat, &net->weights_matrix[i]);

        activationFunc(&tmp_mat);

        cloneMatrix(&tmp_mat_ptr[i], &tmp_mat);

        delMatrix(&tmp_mat);

        //printf("Printing Output of Layer #%d\n", i);
        //printMatrix(&tmp_mat_ptr[i]);
        //printf("\n");
    }

    initMatrix_Zeros(&tmp_mat_ptr[0]);

    for(int i=0; i < tmp_mat_ptr[0].col; i++){
        tmp_mat_ptr[0].data[0][i] = input[i];
    }

    return tmp_mat_ptr;
}

void activationFunc(matrix *m1){
    for(int i=0; i < m1->row; i++){
        for(int j=0; j < m1->col; j++){

            //Activation using sigmoid function.
            // e^x / (e^x + 1)
            m1->data[i][j] = exp(m1->data[i][j]) / (exp(m1->data[i][j]) + 1);
        }
    }
}

//Prints the net
void printANN(FC_ANN *net){
    printf("------------ Network Topology ------------\n");
    printf(" * Input Size         = %d\n", net->layer_sizes[0]);
    printf(" * Output Size        = %d\n", net->layer_sizes[net->n_layers-1]);
    printf(" * Num Hidden Layers  = %d\n", net->n_layers);
    printf(" * Hidden layer Sizes = | ");
    for(int i=0; i < net->n_layers; i++){
        printf("%d ", net->layer_sizes[i]);
    }
    printf("|\n");
    printf("------------------------------------------\n");
    printf("------------------------------------------\n\n");
    printf("------------ Network Weights -------------\n");
    for(int i=0; i < net->n_layers; i++) {
        printf("------------ Hidden Layer #%d ------------ \n", i);
        printMatrix(&net->weights_matrix[i]);
    }
}