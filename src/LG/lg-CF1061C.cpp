#include <cstdio>
#include <iostream>

constexpr int MAX_N = 1000050;
constexpr int MOD = 1e9 + 7;

int f[MAX_N], d[MAX_N];

int calc(int x);

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
    f[0] = 1;
    for (int i = 1; i <= n; i++) {
        int x;
        read(x);
        const auto t = calc(x);
        for (int j = t; j > 0; j--) {
            f[d[j]] += f[d[j] - 1];
            f[d[j]] %= MOD;
        }
    }

    int ans{};
    for (int i = 1; i <= n; i++) {
        ans += f[i];
        ans %= MOD;
    }
    std::cout << ans << '\n';

    return 0;
}

int calc(int x) {
    int cnt{};
    for (int i = 1; i * i <= x; i++) {
        if (!(x % i)) {
            d[++cnt] = i;
            if (i * i != x) {
                d[++cnt] = x / i;
            }
        }
    }
    return cnt;
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