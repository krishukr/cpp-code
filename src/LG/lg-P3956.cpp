#include <cstdio>
#include <iostream>

constexpr int MAX_M = 105;

constexpr int dx[] = {0, 1, 0, -1};
constexpr int dy[] = {1, 0, -1, 0};

int map[MAX_M][MAX_M], vis[MAX_M][MAX_M];
int m, n;

void dfs(int x, int y, int c, bool m);

template <typename T>
T read();

template <typename T>
void read(T& t);

template <typename T, typename... Args>
void read(T& t, Args&... rest);

int main() {
    std::ios::sync_with_stdio(false);

    read(m, n);
    for (int i = 1; i <= n; i++) {
        int x, y, c;
        read(x, y, c);
        map[x][y] = c + 1;
    }
    for (int i = 1; i <= m; i++) {
        std::fill(vis[i], vis[i] + m + 1, 114514);
    }

    dfs(1, 1, 0, true);
    std::cout << (vis[m][m] == 114514 ? -1 : vis[m][m]) << '\n';

    std::cout << std::flush;
    return 0;
}

void dfs(int x, int y, int c, bool g) {
    if (x < 1 or y < 1 or x > m or y > m) {
        return;
    }
    if (vis[x][y] <= c) {
        return;
    }
    vis[x][y] = c;
    if (x == y and x == m) {
        return;
    }

    for (int i = 0; i < 4; i++) {
        const auto xx = x + dx[i], yy = y + dy[i];
        if (map[xx][yy]) {
            dfs(xx, yy, c + (map[x][y] != map[xx][yy]), true);
        } else if (g) {
            map[xx][yy] = map[x][y];
            dfs(xx, yy, c + 2, false);
            map[xx][yy] = 0;
        }
    }
}

template <typename T>
T read() {
    T x{}, f{1};
    int ch = getchar_unlocked();
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