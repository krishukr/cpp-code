#include <cstdio>
#include <iostream>

using ll = long long;

constexpr int MAX_N = 100050;

ll g[21][MAX_N];
ll f[MAX_N];

template <typename T>
T read();

template <typename T>
void read(T& t);

template <typename T, typename... Args>
void read(T& t, Args&... rest);

int main() {
    std::ios::sync_with_stdio(false);

    ll n, k, p;
    read(n, k, p);
    f[0] = 1;
    for (int i = 1; i <= n; i++) {
        g[0][i] = i % p;
        for (int j = 0; j <= k and (1 << (j + 1) <= i); j++) {
            g[j + 1][i] = g[j][i] * g[j][i - (1 << j)] % p;
        }
        ll t{1};
        for (int j = 0; j <= k and (1 << j) <= i; j++) {
            f[i] += t * f[i - (1 << j)];
            f[i] %= p;
            t *= g[j][i - (1 << j)];
            t %= p;
        }
    }
    std::cout << f[n] << '\n';

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