#include "TrigFunction.h"
#include <cmath>

double TrigFunction::FuncA() {
    double x = 0.5;
    return x + std::pow(x, 3) / 3 + 2 * std::pow(x, 5) / 15;
}