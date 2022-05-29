#include <cstdio>
#include <iostream>

using ull = __uint128_t;

int gui[128];

template <typename T>
T read();

template <typename T>
void read(T& t);

template <typename T, typename... Args>
void read(T& t, Args&... rest);

std::ostream& operator<<(std::ostream& o, const ull& x) {
    if (x > 9) {
        o << (x / 10);
    }
    return (o << (int)(x % 10));
}

int main() {
    freopen("zoo.in", "r", stdin);
    freopen("zoo.out", "w", stdout);
    std::ios::sync_with_stdio(false);

    int n, m, c, k, ans{0};
    read(n, m, c, k);
    ull cnt{0}, res{0};

    for (int i = 1; i <= n; i++) {
        ull x;
        read(x);
        cnt |= x;
    }
    for (int i = 1; i <= m; i++) {
        int x, y;
        read(x, y);
        gui[x] = y;
    }
    for (int i = 0; i <= 63; i++) {
        if ((cnt & (1ull << i)) and gui[i]) {
            gui[i] = 0;
        }
    }
    for (int i = 0; i <= 63; i++) {
        if (gui[i]) {
            ans++;
        }
    }

    res = 1ull << (k - 1);
    res -= n;
    res += (1ull << (k - 1));
    res -= (((1ull << ans) - 1) * (1ull << (k - ans)));
    std::cout << res << '\n';

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