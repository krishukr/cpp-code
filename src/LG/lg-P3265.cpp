#include <algorithm>
#include <cstdio>
#include <iostream>

using ld = long double;

constexpr int MAX_N = 505;
constexpr ld EPS = 1e-8;

struct {
    ld v[MAX_N];
    int w;
} a[MAX_N];

int t[MAX_N];

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
        for (int j = 1; j <= m; j++) {
            read(a[i].v[j]);
        }
    }
    for (int i = 1; i <= n; i++) {
        read(a[i].w);
    }
    std::sort(a + 1, a + n + 1,
              [](const auto& x, const auto& y) { return x.w < y.w; });

    int x{}, c{};
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= m; j++) {
            if (std::abs(a[i].v[j]) < EPS) {
                continue;
            }
            if (t[j]) {
                const auto d = a[i].v[j] / a[t[j]].v[j];
                for (int k = j; k <= m; k++) {
                    a[i].v[k] -= d * a[t[j]].v[k];
                }
            } else {
                t[j] = i;
                x++;
                c += a[i].w;
                break;
            }
        }
    }
    std::cout << x << ' ' << c << '\n';

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