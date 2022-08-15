#include <algorithm>
#include <cstdio>
#include <iostream>
#include <queue>

constexpr int INF = 0x3f3f3f3f;
constexpr int MAX_N = 7000050;

int a[MAX_N], r[MAX_N];
std::queue<int> q1, q2, q3;

int get();

template <typename T>
T read();

template <typename T>
void read(T& t);

template <typename T, typename... Args>
void read(T& t, Args&... rest);

int main() {
    std::ios::sync_with_stdio(false);

    int n, m, q, u, v, t;
    read(n, m, q, u, v, t);
    for (int i = 1; i <= n; i++) {
        read(a[i]);
    }
    std::sort(a + 1, a + n + 1, std::greater<int>{});
    for (int i = 1; i <= n; i++) {
        q1.push(a[i]);
    }

    int d{};
    for (int i = 1; i <= m; i++) {
        const auto x = get() + d;
        r[i] = x;
        const int p = 1.0 * u / v * x;
        q2.push(p - d - q);
        q3.push(x - p - d - q);
        d += q;
    }
    for (int i = t; i <= m; i += t) {
        std::cout << r[i] << ' ';
    }
    std::cout << '\n';

    for (int i = 1; !(q1.empty() and q2.empty() and q3.empty()); i++) {
        const auto x = get();
        if (i % t == 0) {
            std::cout << x + d << ' ';
        }
    }
    std::cout << '\n';

    return 0;
}

int get() {
    const auto r1 = q1.empty() ? -INF : q1.front();
    const auto r2 = q2.empty() ? -INF : q2.front();
    const auto r3 = q3.empty() ? -INF : q3.front();
    const auto mx = std::max({r1, r2, r3});
    if (mx == r1) {
        q1.pop();
    } else if (mx == r2) {
        q2.pop();
    } else if (mx == r3) {
        q3.pop();
    }
    return mx;
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