#include <climits>
#include <cstdio>
#include <cstring>
#include <iostream>
#include <queue>

using ll = long long;

constexpr int dx[] = {0, 1, 0, -1, 0};
constexpr int dy[] = {0, 0, 1, 0, -1};
constexpr int MAX_N = 1050;

int mp[MAX_N][MAX_N];
ll di[3][MAX_N][MAX_N];

struct Node {
    ll d;
    int x;
    int y;

    bool operator<(const Node& x) const { return d > x.d; }
};

int n, m;

void dij(int k, int X, int Y);

template <typename T>
T read();

template <typename T>
void read(T& t);

template <typename T, typename... Args>
void read(T& t, Args&... rest);

int main() {
    std::ios::sync_with_stdio(false);

    int a, b, c;
    read(n, m, a, b, c);
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= m; j++) {
            read(mp[i][j]);
        }
    }

    memset(di, 0x3f, sizeof(di));
    dij(0, 1, a);
    dij(1, n, b);
    dij(2, n, c);

    ll r = (LLONG_MAX >> 1);
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= m; j++) {
            r = std::min(
                r, di[0][i][j] + di[1][i][j] + di[2][i][j] - mp[i][j] * 2);
        }
    }
    std::cout << r << '\n';

    return 0;
}

void dij(int k, int X, int Y) {
    std::priority_queue<Node> q;
    q.push({mp[X][Y], X, Y});
    di[k][X][Y] = mp[X][Y];

    while (!q.empty()) {
        const auto p = q.top();
        q.pop();

        for (int i = 1; i <= 4; i++) {
            const auto x = p.x + dx[i], y = p.y + dy[i];
            if (x < 1 or x > n or y < 1 or y > m) {
                continue;
            }
            if (di[k][x][y] > di[k][p.x][p.y] + mp[x][y]) {
                di[k][x][y] = di[k][p.x][p.y] + mp[x][y];
                q.push({di[k][x][y], x, y});
            }
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