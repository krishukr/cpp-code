#include <cmath>
#include <cstdio>
#include <iostream>
#include <numeric>

using ll = long long;

constexpr int MAX_N = 5050;

ll a[MAX_N];
int f[MAX_N], ans[MAX_N];

int fa[MAX_N];

int find(int x) { return (x == fa[x] ? x : (fa[x] = find(fa[x]))); }

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
        fa[i] = i;
    }
    for (int i = 1; i <= n; i++) {
        read(a[i]);
    }
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j < i; j++) {
            const auto p = a[i] * a[j];
            if (p > 0 and (ll)(std::sqrt(p)) * (ll)(std::sqrt(p)) == p) {
                fa[find(i)] = find(j);
            }
        }
    }

    for (int i = 1; i <= n; i++) {
        std::fill(f, f + n + 10, 0);
        int cnt{};
        for (int j = i; j <= n; j++) {
            if (a[j]) {
                if (f[find(j)] == 0) {
                    f[find(j)] = 1;
                    cnt++;
                }
                ans[cnt]++;
            } else {
                ans[std::max(cnt, 1)]++;
            }
        }
    }

    for (int i = 1; i <= n; i++) {
        std::cout << ans[i] << ' ';
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