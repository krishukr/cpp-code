#include <cmath>
#include <cstdio>
#include <iomanip>
#include <iostream>

const double eps = 1e-5;
bool flag = false;

double m[101][102], ans[101];

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
            if (std::abs(m[j][i] - m[t][i]) <= eps) {
                t = j;
            }
        }
        for (int j = 0; j <= n; j++) {
            std::swap(m[i][j], m[t][j]);
        }
    }

    for (int i = 0; i < n; i++) {
        if (std::abs(m[i][i]) <= eps) {
            if (m[i][n]) {
                std::cout << "-1\n";
                return 0;
            } else {
                flag = true;
            }
            continue;
        }

        ans[i] = m[i][n] / m[i][i];
        if (!ans[i]) {
            ans[i] = 0.0;
        }
    }

    if (flag) {
        std::cout << "0\n";
        return 0;
    }

    for (int i = 0; i < n; i++) {
        std::cout << "x" << i + 1 << "=";
        std::cout << std::fixed << std::setprecision(2) << ans[i] << '\n';
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