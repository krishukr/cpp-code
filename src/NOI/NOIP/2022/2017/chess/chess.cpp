#include <cstdio>
#include <iostream>

constexpr int MAX_N = 105;
constexpr int INF = 0x3f3f3f3f;

constexpr int dx[] = {1, 0, -1, 0};
constexpr int dy[] = {0, 1, 0, -1};

int mp[MAX_N][MAX_N];
int mem[MAX_N][MAX_N];
bool vis[MAX_N][MAX_N];
int m, n;
int ans = INF;

void dfs(int x, int y, int c, bool g);

template <typename T>
T read();

template <typename T>
void read(T& t);

template <typename T, typename... Args>
void read(T& t, Args&... rest);

int main() {
    freopen("chess.in", "r", stdin);
    freopen("chess.out", "w", stdout);
    std::ios::sync_with_stdio(false);

    read(m, n);
    for (int i = 1; i <= m; i++) {
        for (int j = 1; j <= m; j++) {
            mp[i][j] = -1;
        }
    }
    for (int i = 1; i <= n; i++) {
        int x, y;
        read(x, y);
        read(mp[x][y]);
    }

    dfs(1, 1, 0, true);
    std::cout << (ans == INF ? -1 : ans) << '\n';

    std::cout << std::flush;
    fclose(stdin);
    fclose(stdout);
    return 0;
}

void dfs(int x, int y, int c, bool g) {
    if (ans <= c) {
        return;
    }
    if (vis[x][y] and mem[x][y] <= c) {
        return;
    } else {
        mem[x][y] = c;
        vis[x][y] = true;
    }
    if (x == m and y == m) {
        ans = std::min(ans, c);
        return;
    }

    for (int i = 0; i < 4; i++) {
        const int nx = x + dx[i], ny = y + dy[i];
        if (nx < 1 or ny < 1 or nx > m or ny > m) {
            continue;
        }
        if (mp[nx][ny] != -1) {
            if (mp[nx][ny] == mp[x][y]) {
                dfs(nx, ny, c, true);
            } else {
                dfs(nx, ny, c + 1, true);
            }
        } else if (g) {
            mp[nx][ny] = mp[x][y];
            dfs(nx, ny, c + 2, false);
            mp[nx][ny] = -1;
        }
    }
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