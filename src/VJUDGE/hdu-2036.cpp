#include <cmath>
#include <cstdio>
#include <iomanip>
#include <iostream>

template <typename T>
T read();

int main() {
    std::ios::sync_with_stdio(false);

    while (true) {
        int n = read<int>();
        if (!n) {
            break;
        }

        auto* x = new int[n + 5]{};
        auto* y = new int[n + 5]{};
        for (int i = 1; i <= n; i++) {
            x[i] = read<int>();
            y[i] = read<int>();
        }

        double sum = (x[n] * y[1] - y[n] * x[1]);
        for (int i = 1; i < n; i++) {
            sum += (x[i] * y[i + 1] - y[i] * x[i + 1]);
        }
        std::cout << std::fixed << std::setprecision(1) << std::abs(sum) / 2.0
                  << '\n';
    }

    return 0;
}

template <typename T>
T read() {
    T x = 0, f = 1;
    char ch = getchar();
    while (!isdigit(ch)) {
        if (ch == '-') f = -1;
        ch = getchar();
    }
    while (isdigit(ch)) {
        x = x * 10 + ch - 48;
        ch = getchar();
    }
    return x * f;
}