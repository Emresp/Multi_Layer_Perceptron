#ifndef MLP_CORE_NETWORK_H
#define MLP_CORE_NETWORK_H
#include "layer.h"

//Oluşturmuş olduğumuz katmanların karışmasını önlemek ve kullanılabilirliği artırmak için ağdaki tüm katmanları ve katman sayısını bir arada tutar
typedef struct
{
    int layer_count;
    Layer** layers;

}Network;

//Ana ağ yapısını oluşturmak için
Network* create_network();

//Oluşturmuş olduğumuz katmanlarız ağ eklemek için gerekli fonksiyon. 2 adet paraemtere alır ağa eklencek katmanın adresi ve eklendiği ağ adresi
void add_layer(Layer* layer,Network* network);

//Oluşturduğumuz ağı yıkmamız gerekirse tahsil ettiğimiz belekleri kapatmamız lazım
//Tek bir parametre alır bu para matre oluşturduğumuz ağın adresidir
void free_network(Network* net);


#endif //MLP_CORE_NETWORK_H