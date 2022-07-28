#include <cstdio>
#include <iostream>

using ll = long long;

template <typename T>
T quick_pow(T a, T b, T m);

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
    if (n == 4) {
        std::cout << "YES\n1\n3\n2\n4\n";
        return 0;
    }
    for (int i = 2; i * i <= n; i++) {
        if (!(n % i)) {
            std::cout << "NO\n";
            return 0;
        }
    }

    std::cout << "YES\n1\n";
    for (int i = 2; i < n; i++) {
        std::cout << 1ll * i * quick_pow<ll>(i - 1, n - 2, n) % n << '\n';
    }
    if (n > 1) {
        std::cout << n << '\n';
    }

    return 0;
}

template <typename T>
T quick_pow(T a, T b, T m) {
    T r{1};
    while (b) {
        if (b & 1) {
            r = r * a % m;
        }
        a = a * a % m;
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