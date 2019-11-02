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
  b) If u want to die, do bi-directional LSTM.
  c) gru's? rodney wants this lol
2) Matrix concats (vstack, hstack)
  a) Test init_Xavier() - ANN
3) Cross Entropy Loss instead of squared error
  a) 1 class cross entropy
  b) multi class
4) Output (Activation function) - softmax()
5) Send rodney volume example

Rodney -
1) CNNS
  a) pooling
  b) padding
  c) all the ings
  d) convolution
2) Optomizers
  a) Adam
3) Kullback-leibler loss instead of squared error
