#include <cstdio>
#include <iostream>

using ll = long long;

constexpr int MAX_N = 12;

bool v[1 << MAX_N];
ll f[MAX_N][1 << MAX_N];

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
    for (int i = 0; i <= (1 << m) - 1; i++) {
        bool f{}, c{};
        for (int j = m - 1; j >= 0; j--) {
            if ((i >> j) & 1) {
                f |= c;
                c = 0;
            } else {
                c ^= 1;
            }
        }
        v[i] = (f | c) ^ 1;
    }

    f[0][0] = 1;
    for (int i = 1; i <= n; i++) {
        for (int j = 0; j <= (1 << m) - 1; j++) {
            for (int k = 0; k <= (1 << m) - 1; k++) {
                if (j & k or !v[j | k]) {
                    continue;
                }
                f[i][j] += f[i - 1][k];
            }
        }
    }
    std::cout << f[n][0] << '\n';

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