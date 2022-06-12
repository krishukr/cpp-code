#include <bits/stdc++.h>

constexpr int MAX_N = 105;
constexpr int MAX_M = 10050;

int f[MAX_M], p[MAX_N][MAX_N];

template <typename T>
T read();

template <typename T>
void read(T& t);

template <typename T, typename... Args>
void read(T& t, Args&... rest);

int main() {
    freopen("souvenir.in", "r", stdin);
    freopen("souvenir.out", "w", stdout);
    std::ios::sync_with_stdio(false);

    int t, n, m;
    read(t, n, m);
    for (int i = 1; i <= t; i++) {
        for (int j = 1; j <= n; j++) {
            read(p[i][j]);
        }
    }

    for (int i = 1; i < t; i++) {
        memset(f, 0, sizeof(f));
        for (int j = 1; j <= n; j++) {
            for (int k = p[i][j]; k <= m; k++) {
                f[k] = std::max(f[k], f[k - p[i][j]] + p[i + 1][j] - p[i][j]);
            }
        }
        m += f[m];
    }
    std::cout << m << '\n';

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