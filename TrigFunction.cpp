#include "TrigFunction.h"
#include <cmath> 

double TrigFunction::FuncA(int n) {

    double sum = 0.0;
    for (int i = 1; i <= n; ++i) {
        double term = (i % 2 == 0 ? -1 : 1) * (pow(4, i - 1) * (1 - pow(4, i))) / (2 * i);
        sum += term;
    }
    
    return sum;
}