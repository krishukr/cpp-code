#include <cstdio>
#include <iostream>

constexpr int MAX_N = 100050;

int a[MAX_N];
int f[2][MAX_N];

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
    for (int i = 1; i <= n; i++) {
        read(a[i]);
    }
    f[0][1] = f[1][1] = 1;
    for (int i = 2; i <= n; i++) {
        if (a[i] > a[i - 1]) {
            f[0][i] = f[1][i - 1] + 1;
        } else {
            f[0][i] = f[0][i - 1];
        }
        if (a[i] < a[i - 1]) {
            f[1][i] = f[0][i - 1] + 1;
        } else {
            f[1][i] = f[1][i - 1];
        }
    }
    std::cout << std::max(f[0][n], f[1][n]) << '\n';

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