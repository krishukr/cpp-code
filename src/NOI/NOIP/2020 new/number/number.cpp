#include <cstdio>
#include <iostream>

using ll = long long;

constexpr int MAX_N = 1005;

int mp[MAX_N][MAX_N];
ll f[2][MAX_N][MAX_N];

template <typename T>
T read();

template <typename T>
void read(T& t);

template <typename T, typename... Args>
void read(T& t, Args&... rest);

int main() {
    freopen("number.in", "r", stdin);
    freopen("number.out", "w", stdout);
    std::ios::sync_with_stdio(false);

    int n, m;
    read(n, m);
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= m; j++) {
            read(mp[j][i]);
        }
    }
    std::swap(n, m);

    for (int i = 0; i <= n + 1; i++) {
        for (int j = 0; j <= m + 1; j++) {
            f[0][i][j] = f[1][i][j] = -1e12;
        }
    }
    f[0][1][1] = f[1][1][1] = mp[1][1];

    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= m; j++) {
            if (i > 1) {
                f[0][i][j] = std::max(
                    f[0][i][j],
                    std::max(f[0][i - 1][j], f[1][i - 1][j]) + mp[i][j]);
                f[1][i][j] = std::max(
                    f[1][i][j],
                    std::max(f[0][i - 1][j], f[1][i - 1][j]) + mp[i][j]);
            }
            if (j > 1) {
                f[0][i][j] = std::max(f[0][i][j], f[0][i][j - 1] + mp[i][j]);
            }
        }
        for (int j = m - 1; j > 0; j--) {
            f[1][i][j] = std::max(f[1][i][j], f[1][i][j + 1] + mp[i][j]);
        }
    }
    std::cout << std::max(f[0][n][m], f[1][n][m]) << '\n';

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