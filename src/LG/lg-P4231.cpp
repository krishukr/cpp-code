#include <climits>
#include <cstdio>
#include <iostream>

using ll = long long;

constexpr int MAX_N = 10000050;

ll a[MAX_N], b[MAX_N], c[MAX_N];

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
    for (int i = 1; i <= m; i++) {
        int l, r, s, e;
        read(l, r, s, e);
        const auto d = (e - s) / (r - l);
        a[l + 0] += s;
        a[l + 1] += d - s;
        a[r + 1] -= d + e;
        a[r + 2] += e;
    }

    ll mx{LLONG_MIN}, as{};
    for (int i = 1; i <= n; i++) {
        b[i] = b[i - 1] + a[i];
        c[i] = c[i - 1] + b[i];
        mx = std::max(mx, c[i]);
        as ^= c[i];
    }
    std::cout << as << ' ' << mx << '\n';

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