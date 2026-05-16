#include <stdio.h>
#include "layer.h"
#include "activations.h"
#include "losses.h"
#include <stdlib.h>

Layer* create_layer(int neurons, int inputs)
{
    //Adresini tutcak biçimde ramde yeni bir katman(layer) için yer açıyoruz
    Layer* new_layer=(Layer*)malloc(sizeof(Layer));

    //Katman özzeliklerimizi atıyoruz bu katmana kaç tane girdi(veri gelicek)
    new_layer->input_count=inputs;

    //Bu katmanda kaç tane nöron buluncak atıyoruz
    new_layer->neuron_count=neurons;

    //Her nöronda girdi(input,veri) kadar katsayı(weights) olması lazım bundan dolayı matiris yapıyoruz zaten ilk önce aşağıdaki gibi satırları oluşturduk

    //Nöron sayısı kadar satır oluştur
    new_layer->weights=(double**)malloc(neurons*sizeof(double*));
    //Nöron sayısı kadar sabit oluştur
    new_layer->biases=(double*)malloc(neurons*sizeof(double));

    //Matrisi oluşturmaya devam ediyoruz satırlar oluştu şimdi sütunları oluşturcaz yani                    nöron1=w1,w2,w3,w4
    //                                                                                                      nöron2=w1,w2,w3,w4
    //sağ tarafta bellirtiğim gibi her satırı gezicez her satırın içine input kadar weights gircez          nöron3=w1,w2,w3,w4
    //iç içe for kullancaz dış döngü nöronları iç döngü o nöronlarda sağ s doğru gidicek gibi düşünebilriz
    //dış döngü nöron iç döngü nöronun içinde döner
    for(int i=0; i<neurons; i++)
    {
        //ilk önce malloc ile az önce oluşan her satıra sütun ekliyor ve matris haline geliyor
        new_layer->weights[i]=(double*)malloc(inputs*sizeof(double));
        //Matirsi oluşan weights 2 boyutlu dizisine girip rastgele değer atama zamanı
        for(int j=0; j<inputs; j++)
        {
            new_layer->weights[i][j]=((double)rand()/(double)RAND_MAX)*2-1; //c dili direk istenilen aralıkta random değer oluşturmadığı için biz manuel o aralığa getirdik değeri
        }
        //bias ilk başta sıfır ile başlayabilir
        new_layer->biases[i]=0;
    }
    return new_layer;
}

double* foward_pass(Layer* layer,double* inputs)
{
    //ilk olarak bu fonksiyonda bir dizi adresi döneceğimiz için döneceğimiz dizinin kalıcı olması lazım ondan dolayı malloc ile ramde yer tahsis ediyoruz
    double* outputs=(double*)malloc(layer->neuron_count*sizeof(double));

    for(int i=0; i<layer->neuron_count; i++)
    {
        outputs[i]=layer->biases[i];

        for(int j=0; j<layer->input_count; j++)
        {
            //Ağırlıklar  ile verileri çarp ve topla ve her veri için bunu ayrı ayrı yapıp ayrı outputlar olarak tut
            outputs[i]=outputs[i]+layer->weights[i][j]*inputs[j];
        }
        outputs[i]=sigmoid(outputs[i]);
    }
    return outputs;
}
