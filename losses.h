#ifndef MLP_CORE_LOSSES_H
#define MLP_CORE_LOSSES_H

//hata hesaplama fonksiyonu. Toplam 3 adet parametre alır: predictions(yapılan tahminler), targets(doğru sonuçlar), size(nöron sayısı)
double calculate_mse(double* predictions, double* targets, int size);

#endif //MLP_CORE_LOSSES_H