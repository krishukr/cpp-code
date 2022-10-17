#include <bits/stdc++.h>

using ll = long long;

constexpr int MOD = 1e9 + 7;

ll p[100];

template <typename T>
T lcm(T a, T b);

template <typename T>
T read();

template <typename T>
void read(T& t);

template <typename T, typename... Args>
void read(T& t, Args&... rest);

int main() {
    std::ios::sync_with_stdio(false);

    p[0] = p[1] = 1;
    for (int i = 2; i < 100; i++) {
        p[i] = lcm(p[i - 1], (ll)i);
    }

    int T;
    read(T);
    while (T--) {
        ll n, a{};
        read(n);
        for (int i = 1; p[i] <= n; i++) {
            a += 1ll * (i + 1) * ((n / p[i]) - (n / p[i + 1])) % MOD;
            a %= MOD;
        }
        std::cout << a << '\n';
    }

    return 0;
}

template <typename T>
T lcm(T a, T b) {
    return a / std::__gcd(a, b) * b;
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