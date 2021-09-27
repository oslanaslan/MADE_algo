#include <iostream>
#include <math.h>

using namespace std;

double EPS = 1e-7;

double target_func(double x) {
    return x * x + sqrt(x);
}

double bin_search(double left, double right, double target_value) {
    int iteration_count = log2((right - left) / EPS);

    for (int i = 0; i < iteration_count; i++) {
        double middle = (right + left) / 2;

        if (target_func(middle) < target_value) {
            left = middle;
        }
        else {
            right = middle;
        }
    }

    return right;
}

int main() {
    double c;
    cin >> c;

    // f(C + 1) = (C + 1)^2 + sqrt(C) >= (C + 1)^2 >= C^2 + 2C + 1 > C = f(x), следовательно,
    // в силу монотонного роста f(x): C + 1 > x, где x - решение f(x) = C.
    // Поэтому можем взять правую границу как C + 1. 
    // f(x) >= 0 \forall x, поэтому поиск начинаем с 0.
    double result = bin_search(0, c + 1, c);

    printf("%.6f\n", result);

    return 0;
}