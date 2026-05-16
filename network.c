#include "network.h"
#include <stdlib.h>

Network* create_network()
{
    Network* network = (Network*)malloc(sizeof(Network));

    network->layer_count=0;
    network->layers=NULL;

    return network;
}

void add_layer(Layer* layer,Network* network)
{
    //Yeni katman adresi eklenceği için bellekte yer açtık şu anki
    network->layers=(Layer**)realloc(network->layers,(network->layer_count + 1) * sizeof(Layer*));

    network->layers[network->layer_count]=layer;

    network->layer_count=network->layer_count+1;
}

