#include <cstdio>
#include <iostream>

using ll = long long;

constexpr int MAX_N = 100050;

int a[MAX_N];

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
        int x, y;
        read(x, y);
        a[x]++;
        a[y]++;
    }

    ll r{};
    for (int i = 1; i <= n; i++) {
        r += 1ll * a[i] * (n - a[i] - 1);
    }
    r >>= 1;
    std::cout << (1ll * n * (n - 1) / 2 * (n - 2) / 3 - r) << '\n';

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