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


def main():
    a = [0, 1, 1, 1, 1]
    c = [2, 2, 2, 2, 2]
    b = [1, 1, 1, 1, 0]
    f = [5, 5, 5, 5, 5]
    solution = efficient_method(a, c, b, f)
    print("x = ", solution)


if __name__ == '__main__':
    main()
