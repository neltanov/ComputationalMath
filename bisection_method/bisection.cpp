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

// double f_derivative(double x, CubicPolinomial* polinom) {
//     return 3 * powf64(x, 2) + 2 * polinom->a * x + polinom->b;
// }

double bisectionOnFiniteSegment(double a, double b, double epsilon, const CubicPolinomial* polinom) {
    double x = 0;
    double c = (b - a) / 2;
    // std::cout << fabs(f(c, polinom)) << std::endl;
    if (fabs(f(c, polinom)) < epsilon) {
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

double bisectionOnInfiniteSegment(double a, double epsilon, bool sign, const CubicPolinomial* polinom) {
    double x = 0;
    double delta = 0.01;
    std::cout << f(a, polinom) << std::endl;
    if (sign) {
        if (f(a, polinom) < 0) {
            std::cout << f(a + delta, polinom) << std::endl;
            if (f(a + delta, polinom) > epsilon) {
                std::cout << fabs(f(delta / 2, polinom)) << std::endl;
                x = bisectionOnFiniteSegment(a, a + delta, epsilon, polinom);
            }
            else {
                x = bisectionOnInfiniteSegment(a + delta, epsilon, sign, polinom);
            }
        }
        if (f(a, polinom) > 0) {
            std::cout << f(a + delta, polinom) << std::endl;
            if (f(a + delta, polinom) < -epsilon) {
                std::cout << fabs(f(delta / 2, polinom)) << std::endl;
                x = bisectionOnFiniteSegment(a, a + delta, epsilon, polinom);
            }
            else {
                x = bisectionOnInfiniteSegment(a + delta, epsilon, sign, polinom);
            }
        }
    }
    else {
        if (f(a - delta, polinom) < -epsilon) {
            x = bisectionOnFiniteSegment(a - delta, a, epsilon, polinom);
        }
        else {
            x = bisectionOnInfiniteSegment(a - delta, epsilon, sign, polinom);
        }
    }

    return x;
}

double derivativeDiscriminant(const CubicPolinomial* polinom) {
    return powf64(polinom->a, 2) - 3 * polinom->b;
}

void solveCubicEquation(const double epsilon, const CubicPolinomial *polinom) {
    double x = 0;
    std::cout << derivativeDiscriminant(polinom) << std::endl;
    if (derivativeDiscriminant(polinom) < -epsilon or abs(derivativeDiscriminant(polinom) < epsilon)) {
        std::cout << fabs(f(0, polinom)) << std::endl;
        if (fabs(f(0, polinom)) < epsilon) {
            x = 0;  
        }
        else {
            x = bisectionOnInfiniteSegment(0, epsilon, polinom);
        }
        std::cout << "Единственный корень кратности 3: " << x << std::endl;
    }
    else if (derivativeDiscriminant(polinom) >= epsilon) {
        double alpha = (-polinom->a - sqrt(derivativeDiscriminant(polinom))) / 3;
        double beta = (-polinom->a + sqrt(derivativeDiscriminant(polinom))) / 3;
        std::cout << "alpha: " << alpha << ", beta: " << beta << std::endl;
        std::cout << f(alpha, polinom) << " " << f(beta, polinom) << std::endl;
        if (f(alpha, polinom) > epsilon && f(beta, polinom) > epsilon) {
            x = bisectionOnInfiniteSegment(alpha, epsilon, polinom);
            std::cout << "Единственный корень кратности 3: " << x << std::endl;
        }
        else if (f(alpha, polinom) < -epsilon && f(beta, polinom) < -epsilon) {
            x = bisectionOnInfiniteSegment(beta, epsilon, polinom);
            std::cout << "Единственный корень кратности 3: " << x << std::endl;
        }
        else if (f(alpha, polinom) > epsilon && fabs(f(beta, polinom)) < epsilon) {
            x = bisectionOnInfiniteSegment(alpha, epsilon, polinom);
            std::cout << "Три корня: " << x << " и " << beta << " кратности 2" << std::endl;
        }
        else if (fabs(f(alpha, polinom)) < epsilon && f(beta, polinom) < -epsilon) {
            x = bisectionOnInfiniteSegment(beta, epsilon, polinom);
            std::cout << "Три корня: " << x << " и " << alpha << " кратности 2" << std::endl;
        }
        else if (f(alpha, polinom) > epsilon && f(beta, polinom) < -epsilon) {
            std::cout << "Три корня: " << 
            bisectionOnInfiniteSegment(alpha, epsilon, polinom) << ", " << 
            bisectionOnFiniteSegment(alpha, beta, epsilon, polinom) << ", " <<
            bisectionOnInfiniteSegment(beta, epsilon, polinom) << std::endl;
        }
        else if (fabs(f(alpha, polinom)) < epsilon && fabs(f(beta, polinom)) < epsilon) {
            x = (alpha + beta) / 2;
            std::cout << "Единственный корень кратности 3: " << x << std::endl;
        }
    }
}

int main(int argc, char *argv[]) {
    double epsilon, a, b, c;
    std::cout << "Введите через пробел параметры epsilon, a, b, c" << std::endl;
    std::cin >> epsilon >> a >> b >> c;

    CubicPolinomial* polinom = new CubicPolinomial(a, b, c);

    solveCubicEquation(epsilon, polinom);

    return 0;
}