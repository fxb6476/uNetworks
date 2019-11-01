#include <stdio.h>
#include <string.h>
#include <math.h>
#include <stdlib.h>
#include "ann.h"
#include <unistd.h>

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

    //Create pointers to biases, each layer is just a matrix of biases...
    net->bias = (matrix *)calloc(net->n_layers, sizeof(matrix));

    //Create pointers to matrix's, each layer is just a matrix of weights...
    net->weights_matrix = (matrix *)calloc(net->n_layers, sizeof(matrix));

    if (!net->bias){
        printf("Error could not allocate matrix buffer for bias!\n");
        return 1;
    }

    if (!net->weights_matrix){
        printf("Error could not allocate matrix buffer for weights!\n");
        return 1;
    }

    net->bias[0].row = 1;
    net->bias[0].col = net->layer_sizes[0];
    initMatrix_Zeros(&net->bias[0]);

    for(int i = 1; i < net->n_layers; i++){
        net->bias[i].row = 1;
        net->bias[i].col = net->layer_sizes[i];
        initMatrix_Ones(&net->bias[i]);
    }

    //Creating first matrix... Input layer.
    net->weights_matrix[0].row = net->layer_sizes[0];
    net->weights_matrix[0].col = 1;
    initMatrix_Ones(&net->weights_matrix[0]);

    for(int i=1; i < net->n_layers; i++){
        net->weights_matrix[i].row = net->layer_sizes[i-1];
        net->weights_matrix[i].col = net->layer_sizes[i];
        initMatrix_Random(&net->weights_matrix[i]);
    }

    printf("Got to the end of init...\n");
    return 0;
}

//Delete network by freeing matrix and array for layer size.
int delANN(FC_ANN *net){
    //Delete each matrix we are pointing to...
    for(int i=0; i < net->n_layers; i++){
        delMatrix(&net->weights_matrix[i]);
    }

    printf("Freed up weights!\n");

    for(int i=0; i < net->n_layers; i++){
        delMatrix(&net->bias[i]);
    }

    printf("Freed up bias!\n");

    //Free out actual pointer.
    free(net->bias);
    free(net->weights_matrix);
    return 0;
}

//Feeds data through ANN and returns matrix's of outputs for each layer.
matrix * feedANN(FC_ANN *net, float *input, int input_size){

    if ( input_size != net->layer_sizes[0] ){
        printf("Error (Feed ANN) - Input data must be the same size as layer 1!\n");
        //ToDo
        // Need to throw an error here instead of just letting this slide!!
    }

    //printf("\nFeeding Data Through Network.... Stand By!!\n\n");

    matrix *tmp_mat_ptr = malloc(sizeof(matrix) * net->n_layers);

    tmp_mat_ptr[0].col = net->layer_sizes[0];
    tmp_mat_ptr[0].row = 1;
    initMatrix_Zeros(&tmp_mat_ptr[0]);

    for(int i=0; i < tmp_mat_ptr[0].col; i++){
        tmp_mat_ptr[0].data[0][i] = input[i];
    }

    for(int i=1; i < net->n_layers; i++){
        tmp_mat_ptr[i].row = 1;
        tmp_mat_ptr[i].col = 1;
        initMatrix_Zeros(&tmp_mat_ptr[i]);
    }

    //printf("Printing Output of Layer #%d\n", 0);
    //printMatrix(&tmp_mat_ptr[0]);
    //printf("\n");

    for(int i=1; i < net->n_layers; i++){
        matrix tmp_mat;
        tmp_mat.row = 1;
        tmp_mat.col = 1;
        initMatrix_Ones(&tmp_mat);

        cloneMatrix(&tmp_mat, &tmp_mat_ptr[i-1]);

        activationFunc(addMatrix(dotMatrix(&tmp_mat, &net->weights_matrix[i]), &net->bias[i]));

        cloneMatrix(&tmp_mat_ptr[i], &tmp_mat);

        delMatrix(&tmp_mat);

        //printf("Printing Output of Layer #%d\n", i);
        //printMatrix(&tmp_mat_ptr[i]);
        //printf("\n");
    }

    return tmp_mat_ptr;
}

//Back propagation of error through network layers...
//Using the chain rule method, things are going to get messy :/
int backProp_ANN(FC_ANN *net, matrix *guessed_outs, float *output, int output_size, float learning_rate){

    if ( output_size != net->layer_sizes[net->n_layers-1] ){
        printf("Error (BackProp ANN) - Output data must be the same size as last layer!\n");
        //ToDo
        // Need to throw an error here instead of just letting this slide!!
    }

    //printf("\nBack Propagating Through Network.... Stand By!!\n\n");

    //Get real outputs we are shooting for...
    matrix tmp_y = {1, net->layer_sizes[net->n_layers-1]};
    initMatrix_Zeros(&tmp_y);

    for(int i=0; i < tmp_y.col; i++){
        tmp_y.data[0][i] = output[i];
    }

    matrix summed_error = {1,1};
    initMatrix_Ones(&summed_error);
    cloneMatrix(&summed_error, &guessed_outs[net->n_layers-1]);
    subMatrix(&summed_error, &tmp_y);

    //printf("Output Error Matrix.\n");
    //printMatrix(&summed_error);
    //printf("\n");

    //float total_error = 0.0;
    //for(int i = 0; i < summed_error.row; i++){
    //    for(int j = 0; j < summed_error.col; j++){
    //        total_error = total_error + (summed_error.data[i][j] * summed_error.data[i][j]);
    //    }
    //}

    //printf("\nCurrent squared summed output error = %.9f!\n", total_error);
    delMatrix(&summed_error);

    matrix cost_with_respect_to_last_layer = {1,1};
    initMatrix_Zeros(&cost_with_respect_to_last_layer);

    for(int round = net->n_layers - 1; round > 0; round--){

        //printf("------------------- Layer %d -------------------\n", round);

        //This holds the change in the current layers weights.
        matrix change_in_weights = {1,1};
        initMatrix_Zeros(&change_in_weights);

        //Last layer of the network has the simplest formula for calculating change in weights and dC/da^(L-1).
        matrix zeta = {1,1};
        matrix place_holder = {1,1};
        initMatrix_Zeros(&zeta);
        initMatrix_Zeros(&place_holder);

        cloneMatrix(&place_holder, &guessed_outs[round-1]);

        // Z = previous_outputs * current_weights + bias.
        cloneMatrix(&zeta, addMatrix(dotMatrix(&place_holder, &net->weights_matrix[round]), &net->bias[round]));

        //printf("Z Matrix....\n");
        //printMatrix(&zeta);
        //printf("\n");

        cloneMatrix(&place_holder, &tmp_y);

        // Zeta = relu'(Z)
        der_of_activ_func(&zeta);

        if(round == net->n_layers - 1) {

            //2 * (y - guessed) * Zeta = 2 * (y - guessed) * relu'(Z)
            elementMult(&zeta, mulScalar(subMatrix(&place_holder, &guessed_outs[round]), 2.0*learning_rate));

        }else{

            // dC/da^(L-1) * Zeta = dC/da^(L-1) * relu'(Z)
            elementMult(&zeta, &cost_with_respect_to_last_layer);
        }

        //printf("Zeta for layer %d.\n", round);
        //printMatrix(&zeta);
        //printf("\n");

        matrix change_in_bias = {1,1};
        initMatrix_Zeros(&change_in_bias);
        cloneMatrix(&change_in_bias, &zeta);

        //printf("Change in bias for layer %d.\n", round);
        //printMatrix(&change_in_bias);
        //printf("\n");

        addMatrix(&net->bias[round], &change_in_bias);

        //Calculating 'cost with respect to previous layer' for last layer! = dC/da^(L-1)
        //This is used in next layer, thus back propagation.
        cloneMatrix(&place_holder, &net->weights_matrix[round]);
        transMatrix(&zeta);
        cloneMatrix(&cost_with_respect_to_last_layer, dotMatrix(&place_holder, &zeta));
        transMatrix(&cost_with_respect_to_last_layer);

        //printf("dC/da^(L-1) Matrix for layer %d.\n", round);
        //printMatrix(&cost_with_respect_to_last_layer);
        //printf("\n");

        transMatrix(&zeta);
        cloneMatrix(&place_holder, &guessed_outs[round - 1]);

        transMatrix(&place_holder);

        //printf("Previous layers output %d.\n", round);
        //printMatrix(&place_holder);
        //printf("\n");

        cloneMatrix(&change_in_weights, dotMatrix(&place_holder, &zeta));

        delMatrix(&zeta);
        delMatrix(&place_holder);

        //printf("Change in current weights for layer %d.\n", round);
        //printMatrix(&change_in_weights);
        //printf("\n");

        addMatrix(&net->weights_matrix[round], &change_in_weights);

        delMatrix(&change_in_weights);

    }

    delMatrix(&tmp_y);
    delMatrix(&cost_with_respect_to_last_layer);

    return 0;
}

void activationFunc(matrix *m1){
    for(int i=0; i < m1->row; i++){
        for(int j=0; j < m1->col; j++){
            //Activation using ReLu.
            //if(m1->data[i][j] <= 0.0) m1->data[i][j] = 0.0;

            //Activation using sigmoid.
            //output = 1 / ( 1 + e^(-x) )
            m1->data[i][j] = 1 / (1 + exp(-1 * m1->data[i][j]));
        }
    }
}
void der_of_activ_func(matrix *m1){
    for(int i=0; i < m1->row; i++){
        for(int j=0; j < m1->col; j++){

            // Derivative of ReLu is estimated as step function at 0.
            // Technically undefined at 0, but we define it as 0 at 0.
            //(m1->data[i][j] > 0) ? (m1->data[i][j] = 1.0) : (m1->data[i][j] = 0.0);

            // Derivative of sigmoid function.
            float sigmoid = 1 / (1 + exp(-1 * m1->data[i][j]));
            m1->data[i][j] = sigmoid * (1 - sigmoid);

        }
    }
}

//Prints the net
void printANN(FC_ANN *net){
    printf("------------ Network Topology ------------\n");
    printf(" * Input Size         = %d\n", net->layer_sizes[0]);
    printf(" * Output Size        = %d\n", net->layer_sizes[net->n_layers-1]);
    printf(" * Num of Layers      = %d\n", net->n_layers);
    printf(" * Layer Sizes        = | ");
    for(int i=0; i < net->n_layers; i++){
        printf("%d ", net->layer_sizes[i]);
    }
    printf("|\n");
    printf("-------------------------------------------\n");
    printf("-------------------------------------------\n\n");
    printf("------------ Network Topology -------------\n");

    for(int i = 0; i < net->n_layers; i++) {
        printf("------------ Biases Layer #%d ------------ \n", i);
        printMatrix(&net->bias[i]);
    }

    for(int i = 0; i < net->n_layers; i++) {
        printf("------------ Hidden Layer #%d ------------ \n", i);
        printMatrix(&net->weights_matrix[i]);
    }
}