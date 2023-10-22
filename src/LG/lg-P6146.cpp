#include <algorithm>
#include <cstdio>
#include <iostream>

using ll = long long;

constexpr int MAX_N = 100050;
constexpr int MOD = 1e9 + 7;

std::pair<int, int> seg[MAX_N];
int s[MAX_N << 1], f[MAX_N];

template <typename T>
T quick_pow(T a, T b);

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
        read(seg[i].first, seg[i].second);
        s[seg[i].second]++;
    }
    for (int i = 1; i <= n + n; i++) {
        s[i] += s[i - 1];
    }
    std::sort(seg + 1, seg + n + 1);

    for (int i = 1; i <= n; i++) {
        f[i] = f[i - 1] * 2ll % MOD;
        f[i] += quick_pow<ll>(2, s[seg[i].first - 1]);
        f[i] %= MOD;
    }
    std::cout << f[n] << '\n';

    std::cout << std::flush;
    return 0;
}

template <typename T>
T quick_pow(T a, T b) {
    T res{1};
    while (b) {
        if (b & 1) {
            res = res * a % MOD;
        }
        a = a * a % MOD;
        b >>= 1;
    }
    return res;
}

template <typename T>
T read() {
    T x{}, f{1};
    int ch = getchar_unlocked();
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