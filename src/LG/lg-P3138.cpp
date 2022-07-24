#include <algorithm>
#include <climits>
#include <cstdio>
#include <iostream>

constexpr int MAX_N = 1050;

struct P {
    int x;
    int y;
    int idx;
} p[MAX_N];

int x[MAX_N], y[MAX_N];
int s[MAX_N][MAX_N];

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
        int x, y;
        read(x, y);
        p[i] = {x, y, i};
    }
    std::sort(p + 1, p + n + 1,
              [](const P& a, const P& b) { return a.x < b.x; });
    for (int i = 1; i <= n; i++) {
        x[p[i].idx] = i;
    }
    std::sort(p + 1, p + n + 1,
              [](const P& a, const P& b) { return a.y < b.y; });
    for (int i = 1; i <= n; i++) {
        y[p[i].idx] = i;
    }

    for (int i = 1; i <= n; i++) {
        s[x[i]][y[i]]++;
    }
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= n; j++) {
            s[i][j] = s[i - 1][j] + s[i][j - 1] - s[i - 1][j - 1] + s[i][j];
        }
    }

    int ans{INT_MAX};
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= n; j++) {
            ans = std::min(
                ans, std::max({s[i][j], s[n][n] - s[i][n] - s[n][j] + s[i][j],
                               s[i][n] - s[i][j], s[n][j] - s[i][j]}));
        }
    }
    std::cout << ans << '\n';

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