#include <algorithm>
#include <cstdio>
#include <iostream>

using ll = long long;

constexpr int MAX_N = 200050;

struct {
    int x;
    ll w;
    ll p;
} a[MAX_N];

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
        a[i].x = i;
        a[i].w = read<ll>();
    }
    for (int i = 1; i <= n; i++) {
        a[i].p = read<ll>();
        if (!a[i].p) {
            std::cout << "Impossible\n";
            return 0;
        }
    }

    std::sort(a + 1, a + n + 1, [](const auto& x, const auto& y) {
        return x.w * (10000 - y.p) < y.w * (10000 - x.p);
    });
    for (int i = 1; i <= n; i++) {
        std::cout << a[i].x << ' ';
    }
    std::cout << '\n';

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