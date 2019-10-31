// Parsing library for the mnist dataset.
// http://yann.lecun.com/exdb/mnist/
// By Felix Blanco
// 
// Mnist dataset used the idx file format...
//
#pragma once
#ifndef mnist_h
#include "matrix.h"

// Function used to grab a certain number of images.
//
// You can also define how many images you would like to offset
// before grabing your images.
// 
// You also need to define the number of rows and columns in a standard image.
//
matrix * grabImages(const char *file_name, int img_offset, int img_count, int img_rows, int img_cols);

// Function used to grab a certain number of image labels.
//
// You can also define how many images you would like to offset
// before grabing your image labels.
// 
matrix * grabLabels(const char *file_name, int label_offset, int label_count);

// Prints idx file info.
void printIdx(const char *file_name);

#endif
