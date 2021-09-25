#include <cmath>
#include <cstdio>
#include <iomanip>
#include <iostream>

// const double eps = 1e-5;

double m[101][102];

template <typename T>
T read();

int main() {
    std::ios::sync_with_stdio(false);

    int n = read<int>();
    for (int i = 0; i < n; i++) {
        for (int j = 0; j <= n; j++) {
            m[i][j] = read<int>();
        }
    }

    for (int i = 0; i < n; i++) {
        int t = i;
        for (int j = i; j < n; j++) {
            if (!(m[j][i] - m[t][i])) {
                // if (std::abs(m[j][i] - m[t][i]) <= eps) {
                t = j;
            }
        }
        for (int j = 0; j <= n; j++) {
            std::swap(m[i][j], m[t][j]);
        }

        if (!(m[i][i])) {
            // if (std::abs(m[i][i]) <= eps) {
            std::cout << "No Solution\n";
            return 0;
        }

        for (int j = i + 1; j <= n; j++) {
            m[i][j] /= m[i][i];
        }
        for (int j = 0; j < n; j++) {
            if (i != j) {
                for (int k = i + 1; k <= n; k++) {
                    m[j][k] -= m[j][i] * m[i][k];
                }
            }
        }
    }

    for (int i = 0; i < n; i++) {
        std::cout << std::fixed << std::setprecision(2) << m[i][n] << '\n';
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