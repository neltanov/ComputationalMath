import numpy as np
import matplotlib.pyplot as plt


def efficient_method(a, c, b, f):
    n = len(f)
    alpha = [0] * n
    beta = [0] * n
    x = [0] * n

    alpha[0] = b[0] / c[0]
    beta[0] = f[0] / c[0]

    for i in range(1, n):
        alpha[i] = b[i] / (c[i] - a[i] * alpha[i - 1])
        beta[i] = (f[i] - a[i] * beta[i - 1]) / (c[i] - a[i] * alpha[i - 1])

    x[n - 1] = beta[n - 1]
    for i in range(n - 2, -1, -1):
        x[i] = beta[i] - alpha[i] * x[i + 1]

    return x


def initial_condition(x):
    return np.where(x < 0, 1, 0)


def exact_solution(x, t):
    return np.where(x - t < 0, 1, 0)


def godunov_scheme(h, r, T):
    a = -1
    b = 10
    x = np.arange(a, b + h, h)
    N = len(x)
    # print(N)
    tau = r * h

    u = np.zeros((int(T / tau) + 1, N))

    # Задаем начальные условия
    u[0] = initial_condition(x)
    for n in range(0, len(u) - 1):
        for i in range(1, N):
            # Разностная схема Годунова
            u[n + 1, i] = u[n, i] - r * (u[n, i] - u[n, i - 1])

        # Граничные условия
        u[n + 1, 0] = 1
        u[n + 1, N - 1] = 0

    return x, u


def implicit_scheme(h, r, T):
    a = -1  # Левый конец отрезка
    b = 10  # Правый конец отрезка
    x = np.arange(a, b + h, h)  # Сетка по пространству
    N = len(x)
    tau = r * h
    u = np.zeros((int(T / tau) + 1, N))  # Массив для хранения значений u
    # Установка начальных условий
    u[0] = initial_condition(x)
    print(u[0])
    alpha = tau / (2 * h)

    a1 = [0] * (N - 1)
    a2 = [0] * (N - 1)
    a3 = [0] * (N - 1)

    a1[0] = 0
    a2[0] = 1
    a3[0] = alpha

    a1[N - 2] = -alpha
    a2[N - 2] = 1
    a3[N - 2] = 0

    for i in range(1, N - 2):
        a1[i] = -alpha
        a2[i] = 1
        a3[i] = alpha

    for n in range(0, len(u) - 1):
        b = [0] * (N - 1)
        b[0] = u[n, 0] + alpha
        for i in range(1, N - 2):
            b[i] = u[n, i]
        b[N - 2] = u[n, N - 2]

        v = efficient_method(a1, a2, a3, b)
        for i in range(0, N - 2):
            u[n + 1, i] = v[i]
        # print(u[n+1])
    return x, u


def main():
    # h = float(input("Введите пространственный шаг h: "))
    # r = float(input("Введите r (r = tau / h): "))
    # T = float(input("Введите время окончания счета T: "))

    h = 0.9
    r = 0.2
    T = 10

    x, u = godunov_scheme(h, r, T)
    x2, u2 = implicit_scheme(h, r, T)
    exact_solution_values = [exact_solution(x, i * r * h) for i in range(len(u))]

    # Графики
    plt.figure(figsize=(8, 6))
    for i in range(0, len(u), len(u) // 3):
        plt.plot(x, u[i], label=f"Годунов t = {i * r * h:.1f}", marker='o', linestyle='dashed')

    for i in range(0, len(u2), len(u2) // 3):
        plt.plot(x2, u2[i], label=f"неявная t = {i * r * h:.1f}", marker='o', linestyle='dashdot')

    # Точное решение
    for i in range(0, len(u), len(u) // 3):
        plt.plot(x, exact_solution_values[i], linestyle='-', label=f"Точное t = {i * r * h:.1f}")

    plt.xlabel('x')
    plt.ylabel('u')
    plt.title('Численные и точное решения линейного уравнения переноса')
    plt.legend()
    plt.grid(True)
    plt.xlim(-1, 10)
    plt.show()


if __name__ == '__main__':
    main()
