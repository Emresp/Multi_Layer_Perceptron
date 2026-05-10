#include "losses.h"
#include <math.h>
double calculate_mse(double* predictions, double* targets, int size)
{
    //Toplam hata oranını tutabilmek için değişken
    double total_mse = 0.0;

    int i;

    //Sırasıyla her nörondan gelen tahminleri dönebilmek için for döngüsü
    for (i = 0; i < size; i++)
    {
        total_mse = total_mse+(0.5*(pow(predictions[i]-targets[i],2)));
    }


    total_mse = total_mse/size;

    return total_mse;
}