#include <cstdio>
#include <iostream>

using ui = unsigned int;

constexpr int MAX_N = 35;

int t[MAX_N][MAX_N];
ui f[MAX_N][MAX_N];

void dfs(int l, int r);

template <typename T>
T read();

template <typename T>
void read(T& t);

template <typename T, typename... Args>
void read(T& t, Args&... rest);

int main() {
    std::ios::sync_with_stdio(false);

    int n;
    read(n);
    for (int i = 1; i <= n; i++) {
        read(f[i][i]);
        f[i][i - 1] = 1;
        t[i][i] = i;
    }

    for (int l = 1; l <= n; l++) {
        for (int i = 1, j = l + 1; j <= n; i++, j++) {
            f[i][j] = f[i + 1][j] + f[i][i];
            t[i][j] = i;
            for (int k = i + 1; k < j; k++) {
                if (f[i][j] < f[i][k - 1] * f[k + 1][j] + f[k][k]) {
                    f[i][j] = f[i][k - 1] * f[k + 1][j] + f[k][k];
                    t[i][j] = k;
                }
            }
        }
    }
    std::cout << f[1][n] << '\n';
    dfs(1, n);
    std::cout << '\n';

    return 0;
}

void dfs(int l, int r) {
    if (l > r) {
        return;
    }
    std::cout << t[l][r] << ' ';
    if (l == r) {
        return;
    }
    dfs(l, t[l][r] - 1);
    dfs(t[l][r] + 1, r);
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