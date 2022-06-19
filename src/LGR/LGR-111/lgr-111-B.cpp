#include <climits>
#include <cstdio>
#include <iostream>

using ll = long long;

inline uint get_next(uint& seed) {
    seed ^= seed << 13;
    seed ^= seed >> 17;
    seed ^= seed << 5;
    return seed;
}

constexpr int MAX_N = 10000050;

ll a[MAX_N];
int fa[MAX_N];

template <typename T>
T read();

template <typename T>
void read(T& t);

template <typename T, typename... Args>
void read(T& t, Args&... rest);

int main() {
    std::ios::sync_with_stdio(false);

    int n;
    uint seed;
    read(n, seed);

    for (int i = 1; i <= n; i++) {
        a[i] = get_next(seed);
    }
    for (int i = 2; i <= n; i++) {
        fa[i] = get_next(seed) % (i - 1) + 1;
    }

    a[0] = LLONG_MAX;
    ll r = a[1];
    for (int i = 2; i <= n; i++) {
        if (a[i] > a[fa[i]]) {
            a[i] = a[fa[i]];
        }
        r += a[i];
    }
    std::cout << r << '\n';

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