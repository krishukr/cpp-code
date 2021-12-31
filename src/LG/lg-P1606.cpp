#include <cstdio>
#include <cstring>
#include <iostream>
#include <queue>

const int MAX_N = 1000050;

struct Node {
    int v;
    int nxt;
} node[MAX_N];

int head[MAX_N];
int cnt;

int mp[35][35];
int n, m, sx, sy, tx, ty;

bool vis[35][35];
bool inq[MAX_N];

const int dx[8] = {2, 1, -1, -2, 2, 1, -1, -2};
const int dy[8] = {1, 2, 2, 1, -1, -2, -2, -1};

long long dis[MAX_N], ans[MAX_N];

void create(int u, int v);

inline int idx(const int& i, const int& j);

void dfs(int p, int x, int y);

template <typename T>
T read();

int main() {
    std::ios::sync_with_stdio(false);

    n = read<int>(), m = read<int>();
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= m; j++) {
            mp[i][j] = read<int>();
            if (mp[i][j] == 3) {
                sx = i;
                sy = j;
            }
            if (mp[i][j] == 4) {
                tx = i;
                ty = j;
            }
        }
    }

    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= m; j++) {
            if (mp[i][j] == 0 or mp[i][j] == 3) {
                memset(vis, 0, sizeof(vis));
                dfs(idx(i, j), i, j);
            }
        }
    }

    std::queue<int> q;
    int s = idx(sx, sy), t = idx(tx, ty);
    for (int i = 1; i <= n * m; i++) {
        dis[i] = 0x3f3f3f3f;
    }

    q.push(s);
    ans[s] = 1;
    dis[s] = 0;
    while (!q.empty()) {
        int p = q.front();
        q.pop();
        inq[p] = false;

        for (int i = head[p]; i; i = node[i].nxt) {
            int v = node[i].v;
            if (dis[v] > dis[p] + 1) {
                dis[v] = dis[p] + 1;
                ans[v] = ans[p];

                if (!inq[v]) {
                    q.push(v);
                    inq[v] = true;
                }
            } else if (dis[v] == dis[p] + 1) {
                ans[v] += ans[p];
            }
        }
    }

    if (dis[t] < 0x3f3f3f3f) {
        std::cout << dis[t] - 1 << '\n' << ans[t] << '\n';
    } else {
        std::cout << -1 << '\n';
    }

    return 0;
}

void create(int u, int v) {
    node[++cnt].v = v;
    node[cnt].nxt = head[u];
    head[u] = cnt;
}

inline int idx(const int& i, const int& j) { return (i - 1) * m + j; }

void dfs(int p, int x, int y) {
    if (vis[x][y]) {
        return;
    }
    vis[x][y] = true;

    for (int i = 0; i < 8; i++) {
        int xx = x + dx[i], yy = y + dy[i];
        if (xx < 1 or yy < 1 or xx > n or yy > m or vis[xx][yy]) {
            continue;
        }

        if (mp[xx][yy] == 1) {
            dfs(p, xx, yy);
        } else if (mp[xx][yy] != 2) {
            vis[xx][yy] = true;
            create(p, idx(xx, yy));
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