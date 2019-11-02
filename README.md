# uNetworks
Toolkit for creating and training neural networks. Built entirely out of standard C libraries. Aimed at bringing machine learning to edge devices.

To build this program for now do:

gcc -o output main.c matrix.c ann.c

./output

Augment main.c to perform testing.


~ To-Do's:

Felix -
1) RNN 
  a) LSTM
    ->) If u want to die, do bi-directional LSTM.
  b) gru's? rodney wants this lol
2) Matrix concats (vstack, hstack)
  a) Test init_Xavier() - ANN

Rodney -
1) CNNS
  a) pooling
  b) padding
  c) all the ings
  d) convolution
2) Optomizers
  a) Adam
