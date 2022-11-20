#include <cstdio>
#include <iostream>

constexpr int MAX_N = 32050;
constexpr int MAX_M = 65;

int c[3][MAX_M], v[3][MAX_M];
int f[MAX_N];

template <typename T>
T read();

template <typename T>
void read(T& t);

template <typename T, typename... Args>
void read(T& t, Args&... rest);

int main() {
    std::ios::sync_with_stdio(false);

    int n, m;
    read(n, m);
    for (int i = 1; i <= m; i++) {
        int x, y, z;
        read(x, y, z);
        c[z ? (c[1][z] ? 2 : 1) : 0][z ? z : i] = x;
        v[z ? (v[1][z] ? 2 : 1) : 0][z ? z : i] = y;
    }
    for (int i = 1; i <= m; i++) {
        for (int j = n; j >= 0; j--) {
            if (j >= c[0][i]) {
                f[j] = std::max(f[j], f[j - c[0][i]] + c[0][i] * v[0][i]);
            }
            if (j >= c[0][i] + c[1][i]) {
                f[j] =
                    std::max(f[j], f[j - c[0][i] - c[1][i]] +
                                       c[0][i] * v[0][i] + c[1][i] * v[1][i]);
            }
            if (j >= c[0][i] + c[2][i]) {
                f[j] =
                    std::max(f[j], f[j - c[0][i] - c[2][i]] +
                                       c[0][i] * v[0][i] + c[2][i] * v[2][i]);
            }
            if (j >= c[0][i] + c[1][i] + c[2][i]) {
                f[j] =
                    std::max(f[j], f[j - c[0][i] - c[1][i] - c[2][i]] +
                                       c[0][i] * v[0][i] + c[1][i] * v[1][i] +
                                       c[2][i] * v[2][i]);
            }
        }
    }
    std::cout << f[n] << '\n';

    return 0;
}

template <typename T>
T read() {
    T x = 0, f = 1;
    char ch = getchar_unlocked();
    while (!isdigit(ch)) {
        if (ch == '-') f = -1;
        ch = getchar_unlocked();
    }
    while (isdigit(ch)) {
        x = x * 10 + ch - 48;
        ch = getchar_unlocked();
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