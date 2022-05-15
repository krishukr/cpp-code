#include <algorithm>
#include <cstdio>
#include <iostream>

using ll = long long;

constexpr int MAX_N = 1000050;

int a[MAX_N];
int s[MAX_N];

template <typename T>
T read();

template <typename T>
void read(T& t);

template <typename T, typename... Args>
void read(T& t, Args&... rest);

int main() {
    std::ios::sync_with_stdio(false);

    int n, c, q;
    read(n, c, q);
    for (int i = 1; i <= n; i++) {
        read(a[i]);
    }

    while (q--) {
        int m;
        read(m);
        for (int i = 1; i <= m; i++) {
            read(s[i]);
        }
        std::sort(s + 1, s + m + 1, [](const int& x, const int& y) {
            return a[x] - 2 * a[y] < a[y] - 2 * a[x];
        });

        ll res{};
        for (int i = 1; i + 1 <= m; i++) {
            res += a[s[i]] - 2 * a[s[i + 1]] + c;
        }
        std::cout << res << '\n';

        std::fill_n(s + 1, m + 1, 0);
    }

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