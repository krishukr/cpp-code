#include <bits/stdc++.h>

using namespace std;

const int M = 2e5 + 5, N = 1e4 + 5;

int val[N], head[M], nxt[M], to[M], sta[N], col[N], dp[N], top, tot, cnt, n, m;
bool vis[N];

vector<int> mmp[M], scc[M];

void add(int f, int t) { nxt[++cnt] = head[f], head[f] = cnt, to[cnt] = t; }

void dfs1(int v) {
    int i;
    for (vis[v] = 1, i = head[v]; i; i = nxt[i])
        if (!vis[to[i]]) dfs1(to[i]);
    sta[++top] = v;
}

void dfs2(int v) {
    int i;
    for (vis[v] = 1, scc[tot].push_back(v), col[v] = tot, dp[tot] += val[v],
        i = mmp[v].size() - 1;
         i >= 0; --i)
        if (!vis[mmp[v][i]]) dfs2(mmp[v][i]);
}

void dfs3(int v) {
    if (vis[v]) return;
    vis[v] = 1;
    int i, j, mx = 0, t;
    for (i = scc[v].size() - 1; i >= 0; --i)
        for (j = mmp[scc[v][i]].size() - 1; j >= 0; --j) {
            t = col[mmp[scc[v][i]][j]];
            if (t == v) continue;
            if (!vis[t]) dfs3(t);
            mx = max(mx, dp[t]);
        }
    dp[v] += mx;
}

int main() {
    scanf("%d%d", &n, &m);
    for (int i = 1; i <= n; ++i) scanf("%d", &val[i]);
    for (int i = 1, a, b; i <= m; ++i)
        scanf("%d%d", &a, &b), add(b, a), mmp[a].push_back(b);
    int i, mx = 0;
    for (i = 1; i <= n; ++i)
        if (!vis[i]) dfs1(i);
    memset(vis, 0, sizeof(vis));
    for (i = top; i >= 1; --i)
        if (!vis[sta[i]]) ++tot, dfs2(sta[i]);
    memset(vis, 0, sizeof(vis));
    for (i = 1; i <= tot; ++i)
        if (!vis[i]) dfs3(i);
    for (int i = 1; i <= tot; ++i) mx = max(mx, dp[i]);
    printf("%d", mx);
}