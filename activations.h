#ifndef MLP_CORE_ACTIVATIONS_H
#define MLP_CORE_ACTIVATIONS_H
//Sigmoid fonksiyonu
double sigmoid(double outputs);

//Backpropagation aşamasında kullanılcak hatayı düzeltmek için türevi alınmış sigmoid fonksiyonudur
double sigmoid_derivative(double outputs);

#endif //MLP_CORE_ACTIVATIONS_H