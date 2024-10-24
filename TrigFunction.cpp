#include "TrigFunction.h"
#include <cmath> 

double TrigFunction::FuncA(int n) {
    if (n < 1) return 0.0; 
    return 1.0 + (1.0/3.0) + (2.0/15.0);
}