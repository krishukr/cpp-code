#include <cstdio>
#include <iostream>

using ll = long long;

constexpr int MAX_N = 100050;

ll c[MAX_N];

template <typename T>
T read();

template <typename T>
void read(T& t);

template <typename T, typename... Args>
void read(T& t, Args&... rest);

int main() {
    freopen("fight.in", "r", stdin);
    freopen("fight.out", "w", stdout);
    std::ios::sync_with_stdio(false);

    int n;
    read(n);
    for (int i = 1; i <= n; i++) {
        read(c[i]);
    }
    ll m, p, s1, s2;
    read(m, p, s1, s2);

    ll d{};
    for (int i = 1; i <= n; i++) {
        d += c[i] * (m - i);
    }
    d += s1 * (m - p);
    auto r = m + (ll)(1.0 * d / s2 + 0.5 * (d < 0 ? -1 : 1));
    if (r > n) {
        r = n;
    }
    if (r < 1) {
        r = 1;
    }
    std::cout << r << '\n';

    std::cout << std::flush;
    fclose(stdin);
    fclose(stdout);
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