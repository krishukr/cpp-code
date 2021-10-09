#include <cstdio>
#include <iomanip>
#include <iostream>

const int MAX_N = 15;

double m[MAX_N][MAX_N];

int main() {
    int n;
    std::cin >> n;
    n++;

    for (int i = 1; i <= n; i++) {
        for (int j = 1; j < n; j++) {
            std::cin >> m[i][j];
            m[i][n + 1] -= m[i][j] * m[i][j];
            m[i][j] *= -2.0;
        }
        m[i][n] = 1.0;
    }

    for (int i = 1; i <= n; i++) {
        int k = i;
        for (int j = k + 1; j <= n; j++) {
            if (std::abs(m[k][i]) < std::abs(m[j][i])) {
                k = j;
            }
        }

        std::swap(m[i], m[k]);

        for (int j = i + 1; j <= n + 1; j++) {
            m[i][j] /= m[i][i];
        }
        m[i][i] = 1;

        for (int j = 1; j <= n; j++) {
            if (i != j) {
                for (int k = i + 1; k <= n + 1; k++) {
                    m[j][k] -= m[j][i] * m[i][k];
                }
                m[j][i] = 0;
            }
        }
    }

    for (int i = 1; i < n; i++) {
        std::cout << std::fixed << std::setprecision(3) << m[i][n + 1] << ' ';
    }
    std::cout << '\n';

    return 0;
}