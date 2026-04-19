#ifndef MLP_CORE_LAYER_H
#define MLP_CORE_LAYER_H
typedef struct
{
    double** weights;//Katmanlarda birde fazla nöron olabileceği için çift pointerlı şekilde oluştuyoruz yani bu bir matris oluyor. weights[i][j] gibi i. nöronun j. ağırlığı
    double* biases;  //Sabit sayımızda her nöronda bir tane olacağı için bunuda dizi yapıyourz.
    double input_count; // Kaç tane girdiği gelicek. Kaç veri var
    int neuron_count;     //Bir katmanda kaç tane nöron olacağını tutan değişken
}Layer;

//Katman oluşturma fonksiyonu
//Bu fonksiyon 2 adet parametre alır aldığı parametreler neurons ve inputs'dur bir katmanda kaç adet nöron olacağını ve kaç adet veri geleceğini alacağın parametersidir
Layer* create_layer(int neurons, int inputs);

//Bu fonksiyon oluşturduğumuz katmanın adresini yani özzeliklerini alır(layer). inputs paramtersi ile işlem yapacğı dizinin adresini alır.
//Gerekli işlemleri yaparak o katmanın çıktısını üretir. bir dizi adresi döner direk tüm dizi değerini veremeyeceiği için ramdeki adresini vericez
double* foward_pass(Layer* layer,double* inputs);


#endif //MLP_CORE_LAYER_H