#include "../TrigFunction.h"

int main(int argc, char* argv[]) {
    TrigFunction trigFunc;

    double result = trigFunc.FuncA(2);

    if (result == 13.5) {
        return 0;
    } else {
        return 1;
    }
}