#include <stdio.h>
#include <math.h>
#include "activations.h"

double sigmoid(double outputs)
{
    return 1.0 / (1.0+exp(-outputs));
}

double sigmoid_derivative(double outputs)
{
    return outputs*(1.0-outputs);
}