#ifndef MLP_CORE_LAYER_H
#define MLP_CORE_LAYER_H
typedef struct
{
    double** weights;//Katmanlarda birde fazla nöron olabileceği için çift pointerlı şekilde oluştuyoruz yani bu bir matris oluyor. weights[i][j] gibi i. nöronun j. ağırlığı
    double* biases;  //Sabit sayımızda her nöronda bir tane olacağı için bunuda dizi yapıyourz.
    int input_count; // Kaç tane girdiği gelicek. Kaç veri var
    int neuron_count;     //Bir katmanda kaç tane nöron olacağını tutan değişken
    double* deltas; //Backpropagation yapılırken nöronlardaki değişim miktarını tutmak için
    double* inputs;
    double* outputs;
}Layer;

//Katman oluşturma fonksiyonu
//Bu fonksiyon 2 adet parametre alır aldığı parametreler neurons ve inputs'dur bir katmanda kaç adet nöron olacağını ve kaç adet veri geleceğini alacağın parametersidir
Layer* create_layer(int neurons, int inputs);

//Bu fonksiyon oluşturduğumuz katmanın adresini yani özzeliklerini alır(layer). inputs paramtersi ile işlem yapacğı dizinin adresini alır.
//Gerekli işlemleri yaparak o katmanın çıktısını üretir. bir dizi adresi döner direk tüm dizi değerini veremeyeceiği için ramdeki adresini vericez
double* foward_pass(Layer* layer,double* inputs);

// Bir katmanı ve içindeki tüm dinamik bellekleri (ağırlıklar, biaslar) temizler.
//Tek bir parametre alır Katman adresini
void free_layer(Layer* layer);


//Çıkış katmanının delta değerini hesaplayan formül
//İki adet parametre alır bunlardan bir katman adresi, Diğeri ise beklenen çıktı
void calculate_output_layer_delta(Layer* layer,double* targets);

//Gizli katmanlardaki delta değerini bulmak için
void calculate_hidden_layer_delta(Layer* layer, Layer* next_layer);

void update_weights(Layer* layer, double learning_rate);


#endif //MLP_CORE_LAYER_H