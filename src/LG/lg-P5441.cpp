#include <cstdio>
#include <iostream>

const int MAX_N = 150;

bool m[MAX_N][MAX_N];

template <typename T>
T read();

int main() {
    std::ios::sync_with_stdio(false);

    int n = read<int>();
    if (n == 1) {
        std::cout << "0\n0\n";
        return 0;
    }

    std::cout << n * (n - 3) * (n * n + 6 * n - 31) / 48 << '\n';

    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= (n + 1) / 2; j++) {
            m[i][(i + j - 1) % n + 1] = true;
        }
    }

    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= n; j++) {
            std::cout << m[i][j] << ' ';
        }
        std::cout << '\n';
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