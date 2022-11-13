#include <algorithm>
#include <cstdio>
#include <iostream>

constexpr int MAX_N = 100050;
constexpr int MAX_M = 1000000;

int a[MAX_N];

struct B {
    int l;
    int r;
} b[MAX_N];

int d[(MAX_M << 1) + 50];

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
        read(a[i]);
    }
    for (int i = 1; i <= m; i++) {
        read(b[i].l, b[i].r);
    }
    std::sort(b + 1, b + m + 1, [](const B& x, const B& y) {
        return x.l == y.l ? x.r < y.r : x.l < y.l;
    });
    int cnt = 1;
    for (int i = 2; i <= m; i++) {
        if (b[i].l <= b[cnt].r) {
            b[cnt].r = std::max(b[cnt].r, b[i].r);
        } else {
            b[++cnt] = b[i];
        }
    }

    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= cnt; j++) {
            d[b[j].l - a[i] + MAX_M]++;
            d[b[j].r - a[i] + 1 + MAX_M]--;
        }
    }
    for (int i = 1; i <= MAX_M << 1; i++) {
        d[i] += d[i - 1];
    }

    int a1{}, a2{};
    for (int i = 0; i <= MAX_M << 1; i++) {
        if (a1 < d[i]) {
            a1 = d[i];
            a2 = std::abs(i - MAX_M);
        } else if (a1 == d[i]) {
            a2 = std::min(a2, std::abs(i - MAX_M));
        }
    }
    std::cout << a2 << ' ' << a1 << '\n';

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