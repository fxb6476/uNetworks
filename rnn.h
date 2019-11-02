/*
 * Felix Blanco
 * - Defines rnn structure, functions, initializers, etc.
 * - ToDO
 * 1) Literally every thing lol
 *   a) Research how RNN's work -> network topology, what they do, how they work, how they are used.
 *   b) Rodney said something about LSTM and adding that in, whatever that is lol.
 */

#pragma once
#ifndef rnn_h

typedef struct{
    int n_layers;
    int layer_sizes[100];
}RNN;

#include "matrix.h"


#endif