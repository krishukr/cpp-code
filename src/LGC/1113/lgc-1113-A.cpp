#include <cmath>
#include <cstdio>
#include <iostream>

using ll = long long;

ll dfs(ll x, ll d);

ll n, k;

template <typename T>
T read();

template <typename T>
void read(T& t);

template <typename T, typename... Args>
void read(T& t, Args&... rest);

int main() {
    std::ios::sync_with_stdio(false);

    read(n, k);
    std::cout << dfs(n, 0) << '\n';

    return 0;
}

ll dfs(ll x, ll d) {
    if (k >= x) {
        return (1ll << d);
    }
    const auto c = std::ceil(1.0 * x / 2.0 / k);
    return c * (1ll << d) + dfs(x - c * k, d + 1);
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