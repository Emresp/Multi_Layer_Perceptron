#include "network.h"
#include "layer.h"
#include <stdlib.h>

Network* create_network()
{
    //Ağ bilgilerini tutabilmek için bellekte yer açıyoruz
    Network* network = (Network*)malloc(sizeof(Network));

    //bellekte oluşan yerlere değişkenlerimizi atıyoruz
    //Değişkenleri sıfırlıyoruz çünkü aldığımız bellekte çöp değerler olabilir
    network->layer_count=0;
    network->layers=NULL;

    //Ağın adresini dönüyoruz
    return network;
}

void add_layer(Layer* layer,Network* network)
{
    //Yeni katman adresi eklenceği için bellekte yer açtık şu anki
    network->layers=(Layer**)realloc(network->layers,(network->layer_count + 1) * sizeof(Layer*));

    //Bellekte yeni açılan yere katamanımızn adresini veriyoruz
    network->layers[network->layer_count]=layer;

    //Yeni katamn eklediğimiz için katman sayısını 1 artırdık
    network->layer_count=network->layer_count+1;
}


void free_network(Network* net)
{
    //Dışardan gelen adres zaten boşsa fonksiyondan çıkabilir güvenlik kontrolü
    if (net==NULL)
    {
        return;
    }

    //Sırasıyla bellekti tüm katmanların yerlerini yıkabilmesi için for döngüsü
    for (int i = 0; i < net->layer_count; i++)
    {
        free_layer(net->layers[i]);
    }

    //Dış kısmıda yıktık create_network fonksiyonunda malloc ile tanımlanan yer
    free(net->layers);

    //Ağın genel adresini tutan belleği de yıktık
    free(net);
}

double* forward_network(Network* network,double* inputs)
{
    //Dışardan gelen verilerin adresini alır
    double* current_inputs=inputs;

    //Tüm katmanları sırasıyla döner
    for (int i = 0; i < network->layer_count; i++)
    {
        //Katmanlar forward pass fonksiyonuna girer ve çıktı üretirler döngü sayesinde her katman bunu yapar
        double* next_inputs= foward_pass(network->layers[i],current_inputs);

        //Önceki katmandan çıktıyı tutabilmek için bellekte yer açmıştık yeni katmana geçildiğinde eskisini silmek için
        if (current_inputs!=inputs)
        {
            free(current_inputs);
        }

        current_inputs=next_inputs;
    }

    return current_inputs;
}

