#include <cstdio>
#include <iostream>

using ll = long long;

constexpr int MAX_N = 100050;
constexpr int MOD = 10007;

int b[MAX_N], c[MAX_N];
int f[2][MAX_N], s[2][MAX_N];

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
    for (int i = 1; i <= n; i++) {
        read(b[i]);
    }
    for (int i = 1; i <= n; i++) {
        read(c[i]);
        f[i & 1][c[i]]++;
        s[i & 1][c[i]] += b[i];
        s[i & 1][c[i]] %= MOD;
    }

    int a{};
    for (int i = 1; i <= n; i++) {
        a += (ll)(i) *
             ((ll)(f[i & 1][c[i]] - 2) * b[i] % MOD + s[i & 1][c[i]]) % MOD;
        a %= MOD;
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