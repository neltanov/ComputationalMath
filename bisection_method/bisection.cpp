#include <iostream>
#include <cmath>

typedef struct CubicPolinomial {
    double a, b, c;

    CubicPolinomial(double a, double b, double c)
    : a(a), b(b), c(c) {}
} CubicPolinomial;

double f(double x, const CubicPolinomial* polinom) {
    return powf64(x, 3) + polinom->a * powf64(x, 2) + polinom->b * x + polinom->c;
}

double f_derivative(double x, CubicPolinomial* polinom) {
    return 3 * powf64(x, 2) + 2 * polinom->a * x + polinom->b;
}

double bisectionOnFiniteSegment(double a, double b, double epsilon, const CubicPolinomial* polinom) {
    double x = 0;
    double c = (b - a) / 2;
    if (abs(f(c, polinom)) < epsilon) {
        x = c;
    }
    else if (f(c, polinom) < -epsilon) {
        x = bisectionOnFiniteSegment(c, b, epsilon, polinom);
    }
    else if (f(c, polinom) > epsilon) {
        x = bisectionOnFiniteSegment(a, c, epsilon, polinom);
    }

    return x;
}

double bisectionOnInfiniteSegment(double a, double epsilon, const CubicPolinomial* polinom) {
    double x = 0;
    double delta = 2;
    if (f(a, polinom) < -epsilon) {
        if (f(a + delta, polinom) > epsilon) {
            x = bisectionOnFiniteSegment(a, a + delta, epsilon, polinom);
        }
        else {
            x = bisectionOnInfiniteSegment(a + delta, epsilon, polinom);
        }
    }
    else if (f(a, polinom) > epsilon) {
        if (f(a - delta, polinom) < -epsilon) {
            x = bisectionOnFiniteSegment(a, a - delta, epsilon, polinom);
        }
        else {
            x = bisectionOnInfiniteSegment(a - delta, epsilon, polinom);
        }
    }

    return x;
}

double derivativeDiscriminant(const CubicPolinomial* polinom) {
    return powf64(2 * polinom->a, 2) - 12 * polinom->b;
}

void solveCubicEquation(const double epsilon, const CubicPolinomial *polinom) {
    double x = 0;
    if (derivativeDiscriminant(polinom) < -epsilon or abs(derivativeDiscriminant(polinom)) < epsilon) {
        if (abs(f(0, polinom)) < epsilon) {
            x = 0;
        }
        else {
            x = bisectionOnInfiniteSegment(0, epsilon, polinom);
        }
        std::cout << "Единственный корень: " << x << std::endl;
    }
    else if (derivativeDiscriminant(polinom) >= epsilon) {
        double alpha = (-2 * polinom->a - sqrt(derivativeDiscriminant(polinom))) / 6;
        double beta = (-2 * polinom->a + sqrt(derivativeDiscriminant(polinom))) / 6;
        if (f(alpha, polinom) > epsilon and f(beta, polinom) > epsilon) {
            x = bisectionOnInfiniteSegment(alpha, epsilon, polinom);
            std::cout << "Единственный корень: " << x << std::endl;
        }
        else if (f(alpha, polinom) < -epsilon and f(beta, polinom) < -epsilon) {
            x = bisectionOnInfiniteSegment(beta, epsilon, polinom);
            std::cout << "Единственный корень: " << x << std::endl;
        }
        else if (f(alpha, polinom) > epsilon and abs(f(beta, polinom)) < epsilon) {
            x = bisectionOnInfiniteSegment(alpha, epsilon, polinom);
            std::cout << "Три корня: " << x << " и " << beta << " кратности 2" << std::endl;
        }
        else if (abs(f(alpha, polinom)) < epsilon and f(beta, polinom) < -epsilon) {
            x = bisectionOnInfiniteSegment(beta, epsilon, polinom);
            std::cout << "Три корня: " << x << " и " << alpha << " кратности 2" << std::endl;
        }
        else if (f(alpha, polinom) > epsilon and f(beta, polinom) < -epsilon) {
            std::cout << "Три корня: " << 
            bisectionOnInfiniteSegment(alpha, epsilon, polinom) << ", " << 
            bisectionOnFiniteSegment(alpha, beta, epsilon, polinom) << ", " <<
            bisectionOnInfiniteSegment(beta, epsilon, polinom) << std::endl;
        }
        else if (abs(f(alpha, polinom)) < epsilon and abs(f(beta, polinom)) < epsilon) {
            x = (alpha + beta) / 2;
            std::cout << "Единственный корень: " << x << std::endl;
        }
    }
}

int main(int argc, char *argv[]) {
    double epsilon, a, b, c;
    std::cout << "Введите через пробел параметры epsilon, a, b, c" << std::endl;
    std::cin >> a >> b >> c;

    CubicPolinomial* polinom = new CubicPolinomial(a, b, c);

    solveCubicEquation(epsilon, polinom);

    return 0;
}