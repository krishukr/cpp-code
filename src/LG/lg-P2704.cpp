#include <cstdio>
#include <iostream>

constexpr int MAX_N = 105;
constexpr int MAX_M = 1 << 10;

int f[3][MAX_M][MAX_M];
int a[MAX_N];

template <typename T>
T read();

template <typename T>
void read(T& t);

template <typename T, typename... Args>
void read(T& t, Args&... rest);

template <>
char read();

int main() {
    std::ios::sync_with_stdio(false);

    int n, m;
    read(n, m);
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            char ch;
            read(ch);
            a[i] = (a[i] << 1) | (ch == 'H');
        }
    }

    m = 1 << m;
    for (int i = 0; i < (1 << m); i++) {
        if (i & a[0] or i & (i << 1) or i & (i << 2)) {
            continue;
        }
        f[0][0][i] = __builtin_popcount(i);
    }
    for (int i = 0; i < m; i++) {
        for (int j = 0; j < m; j++) {
            if (i & j or i & a[0] or j & a[i] or i & (i << 1) or i & (i << 2) or
                j & (j << 1) or j & (j << 2)) {
                continue;
            }
            f[1][i][j] = __builtin_popcount(i) + __builtin_popcount(j);
        }
    }

    for (int i = 2; i < n; i++) {
        for (int j = 0; j < m; j++) {
            if (j & a[i - 1] or j & (j << 1) or j & (j << 2)) {
                continue;
            }
            for (int k = 0; k < m; k++) {
                if (j & k or k & a[i] or k & (k << 1) or k & (k << 2)) {
                    continue;
                }
                for (int l = 0; l < m; l++) {
                    if (j & l or k & l or l & a[i - 2] or l & (l << 1) or
                        l & (l << 2)) {
                        continue;
                    }
                    f[i % 3][j][k] =
                        std::max(f[i % 3][j][k],
                                 f[(i - 1) % 3][l][j] + __builtin_popcount(k));
                }
            }
        }
    }

    int ans{};
    for (int i = 0; i < m; i++) {
        for (int j = 0; j < m; j++) {
            ans = std::max(ans, f[(n - 1) % 3][i][j]);
        }
    }
    std::cout << ans << '\n';

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

template <>
char read() {
    char ch = getchar_unlocked();
    while (ch != 'P' and ch != 'H') {
        ch = getchar_unlocked();
    }
    return ch;
}