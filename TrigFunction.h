#ifndef TRIG_FUNCTION_H
#define TRIG_FUNCTION_H

#include <vector>

class TrigFunction {
public:
    double FuncA(double x, int n);

private:
    std::vector<double> calculateBernoulliNumbers(int n);
};

#endif