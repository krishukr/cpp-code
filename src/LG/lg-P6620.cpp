#include <cstdio>
#include <iostream>

using ll = long long;

constexpr int MAX_N = 1050;

int a[MAX_N];
int f[MAX_N][MAX_N];

template <typename T>
T quick_pow(T a, T b, T p);

template <typename T>
T read();

template <typename T>
void read(T& t);

template <typename T, typename... Args>
void read(T& t, Args&... rest);

int main() {
    std::ios::sync_with_stdio(false);

    int n, x, p, m;
    read(n, x, p, m);
    for (int i = 0; i <= m; i++) {
        read(a[i]);
    }
    f[m][0] = quick_pow<ll>(x + 1, n - m, p);
    for (int i = m - 1; i >= 0; i--) {
        f[i][0] = 1ll * f[i + 1][0] * (x + 1) % p;
        for (int j = 1; j <= m - i; j++) {
            f[i][j] =
                1ll * (f[i][j - 1] - f[i + 1][j - 1] + p) % p * (n - i) % p;
        }
    }

    int r{0};
    for (int i = 0; i <= m; i++) {
        r += 1ll * f[0][i] * a[i] % p;
        r %= p;
    }
    std::cout << r << '\n';

    return 0;
}

template <typename T>
T quick_pow(T a, T b, T p) {
    T r{1};
    while (b) {
        if (b & 1) {
            r = r * a % p;
        }
        a = a * a % p;
        b >>= 1;
    }
    return r;
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