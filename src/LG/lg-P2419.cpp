#include <bitset>
#include <cstdio>
#include <iostream>

constexpr int MAX_N = 105;

template <typename T>
T read();

template <typename T>
void read(T& t);

template <typename T, typename... Args>
void read(T& t, Args&... rest);

int main() {
    std::ios::sync_with_stdio(false);

    std::bitset<MAX_N> f[MAX_N];
    int n, m;
    read(n, m);
    for (int i = 1; i <= m; i++) {
        int x, y;
        read(x, y);
        f[x][y] = true;
    }

    for (int k = 1; k <= n; k++) {
        for (int i = 1; i <= n; i++) {
            for (int j = 1; j <= n; j++) {
                f[i][j] = f[i][j] or (f[i][k] and f[k][j]);
            }
        }
    }

    int a{};
    for (int i = 1; i <= n; i++) {
        bool flag = true;
        for (int j = 1; j <= n; j++) {
            if (i == j) {
                continue;
            }
            flag = flag and (f[i][j] or f[j][i]);
        }
        a += (int)(flag);
    }
    std::cout << a << '\n';

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