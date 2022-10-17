#include <cstdio>
#include <iostream>

constexpr int MAX_N = 1024;
constexpr int MOD = 19260817;

int a[MAX_N][MAX_N];

template <typename T>
T read();

template <typename T>
void read(T& t);

template <typename T, typename... Args>
void read(T& t, Args&... rest);

int main() {
    std::ios::sync_with_stdio(false);

    for (int i = 1; i <= 1000; i++) {
        for (int j = 1; j <= 1000; j++) {
            a[i][j] = (a[i - 1][j - 1] + a[i - 1][j] + i) % MOD;
        }
    }

    int q;
    read(q);
    while (q--) {
        int x, y;
        read(x, y);
        std::cout << a[y][x] << '\n';
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

template <typename T>
void read(T& t) {
    t = read<T>();
}

template <typename T, typename... Args>
void read(T& t, Args&... rest) {
    t = read<T>();
    read(rest...);
}