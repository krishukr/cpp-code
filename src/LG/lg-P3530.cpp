#include <cstdio>
#include <cstring>
#include <iostream>
#include <stack>

constexpr int MAX_N = 605;
constexpr int MAX_M = 100050;

struct {
    int v;
    int nxt;
    int w;
} node[MAX_M << 1];

int head[MAX_N];
int cnt;

void create(int u, int v, int w);

int dfn[MAX_N], low[MAX_N], col[MAX_N];
bool vis[MAX_N];
int idx, tot;
std::stack<int> stk;

void tarjan(int x);

int dis[MAX_N][MAX_N];
int ans[MAX_N];

template <typename T>
T read();

template <typename T>
void read(T& t);

template <typename T, typename... Args>
void read(T& t, Args&... rest);

int main() {
    std::ios::sync_with_stdio(false);

    int n, m1, m2;
    read(n, m1, m2);
    memset(dis, 0x3f, sizeof(dis));
    for (int i = 1; i <= n; i++) {
        dis[i][i] = 0;
    }

    for (int i = 1; i <= m1; i++) {
        int x, y;
        read(x, y);
        create(x, y, -1);
        create(y, x, 1);
        dis[x][y] = std::min(dis[x][y], -1);
        dis[y][x] = std::min(dis[y][x], 1);
    }
    for (int i = 1; i <= m2; i++) {
        int x, y;
        read(x, y);
        create(x, y, 0);
        dis[x][y] = std::min(dis[x][y], 0);
    }

    for (int i = 1; i <= n; i++) {
        if (!dfn[i]) {
            tarjan(i);
        }
    }
    for (int k = 1; k <= n; k++) {
        for (int i = 1; i <= n; i++) {
            if (col[k] != col[i]) {
                continue;
            }
            for (int j = 1; j <= n; j++) {
                if (col[i] != col[j]) {
                    continue;
                }
                dis[i][j] = std::min(dis[i][j], dis[i][k] + dis[k][j]);
            }
        }
    }
    for (int i = 1; i <= n; i++) {
        if (dis[i][i]) {
            std::cout << "NIE" << '\n';
            return 0;
        }
    }
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= n; j++) {
            if (col[i] != col[j]) {
                continue;
            }
            ans[col[i]] = std::max(ans[col[i]], dis[i][j]);
        }
    }

    int res{};
    for (int i = 1; i <= tot; i++) {
        res += ans[i];
    }
    std::cout << res + tot << '\n';

    return 0;
}

void create(int u, int v, int w) {
    node[++cnt].v = v;
    node[cnt].nxt = head[u];
    node[cnt].w = w;
    head[u] = cnt;
}

void tarjan(int x) {
    dfn[x] = low[x] = ++idx;
    vis[x] = true;
    stk.push(x);
    for (int i = head[x]; i; i = node[i].nxt) {
        const auto v = node[i].v;
        if (!dfn[v]) {
            tarjan(v);
            low[x] = std::min(low[x], low[v]);
        } else if (vis[v]) {
            low[x] = std::min(low[x], low[v]);
        }
    }
    if (dfn[x] == low[x]) {
        int p;
        tot++;
        do {
            p = stk.top();
            stk.pop();
            vis[p] = false;
            col[p] = tot;
        } while (p != x);
    }
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