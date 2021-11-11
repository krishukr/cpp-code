#include <cstdio>
#include <iostream>
#include <stack>

const int MAX_N = 1050;

int w[MAX_N], v[MAX_N], d[MAX_N];
int dfn[MAX_N], fa[MAX_N], low[MAX_N];
bool vis[MAX_N];
int idx, col, m;

int ww[MAX_N], vv[MAX_N], ind[MAX_N];
int dp[MAX_N][MAX_N];

std::stack<int> stk;

void tarjan(int x);

void dfs(int x);

template <typename T>
T read();

class Star {
   public:
    Star() = default;
    ~Star() = default;

    struct Node {
        int v;
        int nxt;
    } node[MAX_N];

    int head[MAX_N];
    int cnt;

    void create(int u, int v);
};

Star *star;

int main() {
    std::ios::sync_with_stdio(false);

    int n = read<int>();
    m = read<int>();
    for (int i = 1; i <= n; i++) {
        w[i] = read<int>();
    }
    for (int i = 1; i <= n; i++) {
        v[i] = read<int>();
    }

    star = new Star();
    for (int i = 1; i <= n; i++) {
        d[i] = read<int>();
        if (d[i]) {
            star->create(d[i], i);
        }
    }

    for (int i = 1; i <= n; i++) {
        if (!dfn[i]) {
            tarjan(i);
        }
    }

    star = new Star();
    for (int i = 1; i <= n; i++) {
        if (fa[i] != fa[d[i]]) {
            star->create(fa[d[i]], fa[i]);
            ind[fa[i]]++;
        }
    }

    for (int i = 1; i <= col; i++) {
        if (!ind[i]) {
            star->create(0, i);
        }
    }
    dfs(0);
    std::cout << dp[0][m] << '\n';

    return 0;
}

void tarjan(int x) {
    dfn[x] = low[x] = ++idx;
    vis[x] = true;
    stk.push(x);

    for (int i = star->head[x]; i; i = star->node[i].nxt) {
        int v = star->node[i].v;
        if (!dfn[v]) {
            tarjan(v);
            low[x] = std::min(low[x], low[v]);
        } else if (vis[v]) {
            low[x] = std::min(low[x], dfn[v]);
        }
    }

    if (low[x] == dfn[x]) {
        int k;
        col++;
        do {
            k = stk.top();
            stk.pop();
            vis[k] = false;

            fa[k] = col;
            ww[col] += w[k];
            vv[col] += v[k];
        } while (k != x);
    }
}

void dfs(int x) {
    for (int i = ww[x]; i <= m; i++) {
        dp[x][i] = vv[x];
    }
    for (int i = star->head[x]; i; i = star->node[i].nxt) {
        int v = star->node[i].v;
        dfs(v);

        int t = m - ww[x];
        for (int j = t; j >= 0; j--) {
            for (int k = 0; k <= j; k++) {
                dp[x][j + ww[x]] =
                    std::max(dp[x][j + ww[x]], dp[v][k] + dp[x][j + ww[x] - k]);
            }
        }
    }
}

void Star::create(int u, int v) {
    node[++cnt].v = v;
    node[cnt].nxt = head[u];
    head[u] = cnt;
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