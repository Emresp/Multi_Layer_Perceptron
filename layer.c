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

    //Her nöronun kendi deltası olması lazımdır. bu değer türev alınarak bulunu geri yayılım aşmasında o nöronun ne kadar sonuca ne kadar etkili olduğu hesaplanır
    //Bu sayede hangi ağırlığın ne kadar güncellenmesi gerek ona karar veririz.
    new_layer->deltas=(double*)malloc(neurons*sizeof(double));

    new_layer->outputs = (double*)malloc(neurons * sizeof(double));

    new_layer->inputs=NULL;




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


    for(int i=0; i<layer->neuron_count; i++)
    {
        layer->outputs[i]=layer->biases[i];

        for(int j=0; j<layer->input_count; j++)
        {
            //Ağırlıklar  ile verileri çarp ve topla ve her veri için bunu ayrı ayrı yapıp ayrı outputlar olarak tut
           layer->outputs[i]=layer->outputs[i]+layer->weights[i][j]*inputs[j];
        }
        layer->outputs[i]=sigmoid(layer->outputs[i]);
    }

    layer->inputs=inputs;


    return layer->outputs;
}

void free_layer(Layer* layer)
{
    //Verilen Katmanadresinde katman var mı kontrolü. Eğer boşsa fonksiyondan direk çıksın
    if (layer == NULL)
    {
        return;
    }

    //Sabit sayının adresini temizlme
    free(layer->biases);

    //Oluşturduğumuz nöronların bellekti delta değerini temizlemek için
    free(layer->deltas);
    //forward_pass aşamsında katmanlarda oluşan çıktıyı temizlemek için
    free(layer->outputs);


    //Tek tek her nörondaki ağırlığı silmesi için döngü
    for(int i=0; i<layer->neuron_count; i++)
    {
        free(layer->weights[i]);
    }

    //Ana diziyi silme işlemi
    free(layer->weights);

    //Genel katmanı silme
    free(layer);
}

void calculate_output_layer_delta(Layer* layer,double* targets)
{
    for(int i=0; i<layer->neuron_count; i++)
    {
        //Çıkış katamanında bulunan nöronların delta değeri
        layer->deltas[i]=(layer->outputs[i]-targets[i])*(sigmoid_derivative(layer->outputs[i]));
    }
}

void calculate_hidden_layer_delta(Layer* layer, Layer* next_layer)
{
    for(int i=0; i<layer->neuron_count; i++)
    {
        double sum=0;

        for (int j=0; j<next_layer->neuron_count; j++)
        {
            sum=sum+next_layer->weights[j][i]*next_layer->deltas[j];
        }
        layer->deltas[i]=sigmoid_derivative(layer->outputs[i])*sum;
    }
}

void update_weights(Layer* layer, double learning_rate)
{
    for (int i=0; i<layer->neuron_count; i++)
    {
        //bias güncelledik
        layer->biases[i]=layer->biases[i]+(learning_rate*layer->deltas[i]);

        for(int j=0; j<layer->input_count; j++)
        {
            //ağırlıkları güncelledik
            layer->weights[i][j]=layer->weights[i][j]+(learning_rate*layer->deltas[i]*layer->inputs[j]);
        }
    }
}
