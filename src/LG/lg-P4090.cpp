#include <cmath>
#include <cstdio>
#include <iomanip>
#include <iostream>

double m[101][102], ans[101];
bool flag = false;

template <typename T>
T read();

int main() {
    std::ios::sync_with_stdio(false);
    srand(time(nullptr));

    int n = read<int>();
    for (int i = 0; i < n; i++) {
        for (int j = 0; j <= n; j++) {
            m[i][j] = read<int>();
        }
    }

    for (int i = 0; i < n; i++) {
        for (int j = i + 1; j < n; j++) {
            int x = rand() % 1001;

            if (x & 1) {
                for (int k = 0; k <= n; k++) {
                    std::swap(m[i][k], m[j][k]);
                }
            }
        }
    }

    for (int i = 0; i < n; i++) {
        int t = i;
        for (int j = i + 1; j < n; j++) {
            if (std::abs(m[j][i]) > std::abs(m[t][i])) {
                t = j;
            }
        }

        if (m[t][i] == 0) {
            continue;
        }

        for (int j = 0; j <= n; j++) {
            std::swap(m[i][j], m[t][j]);
        }

        for (int j = 0; j < n; j++) {
            if (i != j) {
                double t = m[j][i] / m[i][i];
                for (int k = 0; k <= n; k++) {
                    m[j][k] -= m[i][k] * t;
                }
            }
        }
    }

    for (int i = 0; i < n; i++) {
        if (m[i][i] == 0) {
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