#include <cstdio>
#include <iostream>

constexpr int MAX_N = 10000050;
constexpr int MOD = 1e9 + 7;

int f[2][MAX_N];

template <typename T>
T read();

template <typename T>
void read(T& t);

template <typename T, typename... Args>
void read(T& t, Args&... rest);

template <>
void read(char& t);

int main() {
    std::ios::sync_with_stdio(false);

    int n;
    read(n);
    f[0][0] = f[1][0] = 1;
    for (int i = 1; i <= n; i++) {
        char p;
        read(p);
        if (p == '&') {
            f[0][i] = (f[0][i - 1] * 2 % MOD + f[1][i - 1]) % MOD;
            f[1][i] = f[1][i - 1];
        } else if (p == '|') {
            f[0][i] = f[0][i - 1];
            f[1][i] = (f[1][i - 1] * 2 % MOD + f[0][i - 1]) % MOD;
        } else {
            f[0][i] = f[1][i] = (f[0][i - 1] + f[1][i - 1]) % MOD;
        }
    }
    std::cout << f[1][n] << '\n';

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

template <>
void read(char& t) {
    t = 0;
    while (t != '&' and t != '|' and t != '^') {
        t = getchar();
    }
}