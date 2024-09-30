#include "TrigFunction.h"
#include <iostream>
#include <iomanip>
#include <cmath>

int main() {
    TrigFunction trig;
    double x;
    int n;

    std::cout << "Enter x (in radians): ";
    std::cin >> x;
    std::cout << "Enter number of terms: ";
    std::cin >> n; // number of terms

    double result = trig.FuncA(x, n);
    
    std::cout << std::fixed << std::setprecision(10);
    std::cout << "Approximation of tan(" << x << ") using " << n << " terms: " << result << std::endl;
    

    return 0;
}