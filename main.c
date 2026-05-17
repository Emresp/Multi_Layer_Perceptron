#include <stdio.h>
#include <stdlib.h>

#include "layer.h"
#include "network.h"


int main(void)
{
    Network* my_network=create_network();

    double inputs[4] = {5.1 ,3.5, 1.4, 0.2};


    Layer* layer1 = create_layer(2,4);
    add_layer(layer1,my_network);

    Layer* layer2=create_layer(1,2);
    add_layer(layer2,my_network);

    double* predection=forward_network(my_network,inputs);

    printf("Predection:%f",predection[0]);

    free_network(my_network);
    free(predection);

    return 0;
}