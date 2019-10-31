#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include "mnist.h"

matrix * grabImages(const char *file_name, int img_offset, int img_count, int img_rows, int img_cols){

    // Create array of matrix's each contains an image.
    matrix *output = (matrix *)malloc(sizeof(matrix) * img_count);

    int img_size = img_rows * img_cols;

    for (int i = 0; i < img_count; i++){
        // Initializing each matrix to 0's.
        output[i].row = 1;
	output[i].col = img_size;
	initMatrix_Zeros(&output[i]);

    }
    
    FILE *file;

    // Try to grab the file...
    if ( (file = fopen(file_name, "rb")) == NULL){
        printf("Error - Could not open %s file.\n", file_name);
        return output;
    }

    // Offset file pointer so we don't read the idx file header.
    // For mnist image idx files the image data start at an offset of 16 bytes from the start of the file.
    // We will also add the amount of images we want to skip.
    // Each image is 'img_size' bytes so add num_img_to_skip * img_size, to total offset.
    fseek(file, 16 + (img_offset * img_size), SEEK_SET);

    // Now start grabbing data...
    for (int i = 0; i < img_count; i++){

	// This will write 'img_size' bytes to the first row of each matrix.
	// We make each matrix with 1 row. 
        // This makes it easier to pass the data to our neural network, transpose, reshape, etc.

	unsigned char *datz = malloc(img_size);

        fread(datz, 1, img_size, file);

	for(int j = 0; j < img_size; j++){
	    // Copy character data from datz to matrix but typecast to float.
            // Maybe an easier way of doing this?
            // Not sure if you can write a single byte to where a float should be in an array of floats?
            output[i].data[0][j] = (float)datz[j];
	}

	free(datz);
    }

    fclose(file);
    return output;
}

matrix * grabLabels(const char *file_name, int label_offset, int label_count){

    // Fix this so output is something like this y = 5 so output = {0 0 0 0 1 0 0 0 0}



    // Lets start by defining our output matrix.
    matrix *output = (matrix *)malloc(sizeof(matrix) * 1);
    output[0].row = 1;
    output[0].col = label_count;
    initMatrix_Zeros(&output[0]);

    // Now lets work with our file...
    FILE *file;

    // Try to grab the file...
    if ( (file = fopen(file_name, "rb")) == NULL){
        printf("Error - Could not open %s file.\n", file_name);
        return output;
    }

    // Offset file pointer so we don't read the idx file header.
    // For mnist label idx files the label data start at an offset of 8 bytes from the start of the file.
    // We will also add the amount of labels we want to skip.
    // Each label is 1 byte so just add label_offset.
    fseek(file, 8 + label_offset, SEEK_SET);

    // Now lets start actually grabbing data.
    unsigned char *datz = malloc(label_count);

    fread(datz, 1, label_count, file);

    for (int i = 0; i < label_count; i++){

        // Copy data in datz buffer to our matrix but type cast to float.
        output[0].data[0][i] = (float)(datz[i]);

    }

    free(datz);

    fclose(file);
    return output;
}

void printIdx(const char *file_name){
    FILE *file;

    // Try to grab the file...
    if ( (file = fopen(file_name, "rb")) == NULL){
        printf("Error - Could not open %s file.\n", file_name);
    }
    
    // Reading the magic number of the file.

    printf("[+] Information for %s file!\n", file_name);
    fseek(file, 0, SEEK_SET);

    int32_t *magic_num = malloc(sizeof(int32_t) * 1);
    int32_t *num_items = malloc(sizeof(int32_t) * 1);

    fread(magic_num, sizeof(int32_t), 1, file);
    fread(num_items, sizeof(int32_t), 1, file);

    int magic = *magic_num >> 16;
    int items = *num_items >> 16;

    printf("[+] Magic number - %d\n[+] Number of Items - %d\n", magic, items);

    free(magic_num);
    free(num_items);

}
