import math
from enum import Enum


class IntegrationMethods(Enum):
    TRAPEZOID = 1
    SIMPSON = 2
    SOME_QUADRA = 3

a = 5
b = 7


def f(x):
    return math.exp(x) * math.cos(x)


def trapezoid_formula(n):
    res = 0
    h = (b - a) / n
    for i in range(0, n):
        res += (f(a + i * h) + f(a + (i + 1) * h)) * h / 2
    return res


def simpson_formula(n):
    if n % 2 != 0:
        print('Число отрезков должно быть четным!')
        return
    res = f(a) + f(b)
    h = (b - a) / n
    for i in range(1, n):
        x = a + i * h
        if i % 2 == 0:
            factor = 2
        else:
            factor = 4
        res += factor * f(x)
    res *= h / 3
    return res


def some_quadra_formula(n):
    if n % 3:
        print('Число отрезов должно быть кратно трем!')
        return
    res = 3 * f(a) + 3 * f(b)
    h = (b - a) / n
    for i in range(1, n):
        if i % 3 == 0:
            factor = 6
        else:
            factor = 9
        res += factor * f(a + i * h)
    res *= h / 8
    return res


def get_order_of_accuracy(n, integration_formula):
    s1 = 0
    s2 = 0
    s3 = 0
    if integration_formula == IntegrationMethods.TRAPEZOID:
        s1 = trapezoid_formula(n)
        s2 = trapezoid_formula(n * 2)
        s3 = trapezoid_formula(n * 4)
    elif integration_formula == IntegrationMethods.SIMPSON:
        if n % 2 != 0:
            print('Порядок точности для формулы Симпсона определить нельзя!')
            return
        s1 = simpson_formula(n)
        s2 = simpson_formula(n * 2)
        s3 = simpson_formula(n * 4)
    elif integration_formula == IntegrationMethods.SOME_QUADRA:
        if n % 3:
            print('Порядок точности для квадратурной формулы из первого пункта определить нельзя!')
            return
        s1 = some_quadra_formula(n)
        s2 = some_quadra_formula(n * 2)
        s3 = some_quadra_formula(n * 4)
    return math.log2(math.fabs((s1 - s2) / (s2 - s3)))


def main():
    # Точное значение интеграла: 823.72
    n = int(input("Введите количество элементарных отрезков на [a,b]: "))

    print(f'Значение интеграла по формуле трапеций равно {trapezoid_formula(n)}')
    print(f'Значение интеграла по формуле Симпсона равно {simpson_formula(n)}')
    print(f'Значение интеграла по квадратурной формуле из первого пункта задания равно {some_quadra_formula(n)}')

    k1 = get_order_of_accuracy(n, IntegrationMethods.TRAPEZOID)
    k2 = get_order_of_accuracy(n, IntegrationMethods.SIMPSON)
    k3 = get_order_of_accuracy(n, IntegrationMethods.SOME_QUADRA)
    print(f'Порядок точности квадратурной формулы трапеции k = {k1}')
    print(f'Порядок точности квадратурной формулы Симпсона k = {k2}')
    print(f'Порядок точности квадратурной формулы из первого пункта задания k = {k3}')


if __name__ == '__main__':
    main()
