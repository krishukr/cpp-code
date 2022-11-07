#include <algorithm>
#include <cmath>
#include <cstdio>
#include <iostream>

using ll = long long;

constexpr int MAX_N = 100050;

struct {
    double d;
    int i;
    ll c;
} a[MAX_N];

template <typename T>
T read();

template <typename T>
void read(T& t);

template <typename T, typename... Args>
void read(T& t, Args&... rest);

int main() {
    std::ios::sync_with_stdio(false);

    ll n, x, y;
    read(n, x, y);
    for (int i = 1; i <= n; i++) {
        ll xi, yi, c;
        read(xi, yi, c);
        a[i] = {std::sqrt((yi - y) * (yi - y) + (xi - x) * (xi - x)), i, c};
    }
    std::sort(a + 1, a + n + 1, [](const auto& a, const auto& b) {
        return a.d == b.d ? a.i < b.i : a.d < b.d;
    });

    int ans{}, cr{}, cb{};
    for (int i = 1; i <= n; i++) {
        if (a[i].c == 1) {
            cr++;
        } else {
            cb++;
        }
        if (cr >= cb) {
            ans++;
        }
    }
    std::cout << ans << '\n';

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