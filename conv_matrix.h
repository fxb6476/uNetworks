//
// Created by hivemind on 10/29/2019.
//


#pragma once
#ifndef conv_matrix_h

// Void pointer to data so we can initialize matrix's of doubles, floats, chars, etc, any data type.
typedef struct{
    int row;
    int col;
    float **data;
}matrix;


matrix*conv2d(matrix input,matrix filters,int filt_size,char pad_type, int stride);
int init_weights_xavier(matrix *mat);
matrix*pooling(matrix *m1, char type);



#endif
