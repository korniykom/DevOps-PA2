#include "TrigFunction.h"
#include <cmath>
#include <iostream>

std::vector<double> TrigFunction::calculateBernoulliNumbers(int n) {
    std::vector<double> B(n + 1);
    B[0] = 1;
    B[1] = -0.5;
    for (int m = 2; m <= n; m++) {
        B[m] = 0;
        for (int k = 0; k < m; k++) {
            double combination = 1;
            for (int i = 0; i < k + 1; i++) {
                combination *= (m - i + 1.0) / (i + 1.0);
            }
            B[m] -= combination * B[k] / (m - k + 1);
        }
    }
    return B;
}

double TrigFunction::FuncA(double x, int n) {
    if (std::abs(x) >= M_PI / 2) {
        std::cout << "Warning: |x| should be less than π/2 for accurate results." << std::endl;
    }
    
    double result = x;
    std::vector<double> B = calculateBernoulliNumbers(2 * n);
    
    for (int i = 1; i <= n; i++) {
        double term = B[2*i] * std::pow(-4, i) * (1 - std::pow(4, i)) / std::tgamma(2*i + 1) * std::pow(x, 2*i - 1);
        result += term;
    }
    
    return result;
}