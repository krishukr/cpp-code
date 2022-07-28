#include <algorithm>
#include <cstdio>
#include <iostream>

constexpr int MAX_N = 15;

int m[MAX_N][MAX_N];
int f[MAX_N][MAX_N][MAX_N][MAX_N];

template <typename T>
T read();

template <typename T>
void read(T& t);

template <typename T, typename... Args>
void read(T& t, Args&... rest);

int main() {
    std::ios::sync_with_stdio(false);

    int n;
    read(n);
    while (true) {
        int x, y, z;
        read(x, y, z);
        if (!x and !y and !z) {
            break;
        }
        m[x][y] = z;
    }
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= n; j++) {
            for (int k = 1; k <= n; k++) {
                for (int l = 1; l <= n; l++) {
                    f[i][j][k][l] =
                        std::max({f[i - 1][j][k - 1][l], f[i - 1][j][k][l - 1],
                                  f[i][j - 1][k - 1][l],
                                  f[i][j - 1][k][l - 1]}) +
                        m[i][j];
                    if (i != k and j != l) {
                        f[i][j][k][l] += m[k][l];
                    }
                }
            }
        }
    }
    std::cout << f[n][n][n][n] << '\n';

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

template <typename T>
void read(T& t) {
    t = read<T>();
}

template <typename T, typename... Args>
void read(T& t, Args&... rest) {
    t = read<T>();
    read(rest...);
}