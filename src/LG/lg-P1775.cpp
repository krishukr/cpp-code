#include <cstdio>
#include <cstring>
#include <iostream>

constexpr int MAX_N = 305;

int f[MAX_N][MAX_N], s[MAX_N];

template <typename T>
T read();

template <typename T>
void read(T& t);

template <typename T, typename... Args>
void read(T& t, Args&... rest);

int main() {
    std::ios::sync_with_stdio(false);

    memset(f, 0x3f, sizeof(f));
    int n;
    read(n);
    for (int i = 1; i <= n; i++) {
        read(s[i]);
        s[i] += s[i - 1];
    }
    for (int i = 1; i <= n; i++) {
        f[i][i] = 0;
    }

    for (int l = 2; l <= n; l++) {
        for (int i = 1; i <= n - l + 1; i++) {
            for (int j = i + l - 1, k = i; k < j; k++) {
                f[i][j] =
                    std::min(f[i][j], f[i][k] + f[k + 1][j] + s[j] - s[i - 1]);
            }
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