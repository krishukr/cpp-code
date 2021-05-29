#include <cstdio>
#include <cstring>
#include <iostream>
#include <vector>

const int MAX_N = 100010;

struct Node {
    int v;
    int w;
};

std::vector<Node> edge[MAX_N];
bool vis[MAX_N];
int ans, x;

void dfs(int u, int dis);

int main() {
    std::ios::sync_with_stdio(false);

    int u, v, w;
    while (std::cin >> u >> v >> w) {
        edge[u].push_back((Node){v, w});
        edge[v].push_back((Node){u, w});
    }

    dfs(1, 0);
    ans = 0;
    memset(vis, false, sizeof(vis));
    dfs(x, 0);
    printf("%d\n", ans);

    return 0;
}

void dfs(int u, int dis) {
    if (dis > ans) {
        ans = dis;
        x = u;
    }
    vis[u] = true;
    for (int i = 0; i < edge[u].size(); i++) {
        int v = edge[u][i].v;
        if (!vis[v]) {
            dfs(v, dis + edge[u][i].w);
        }
    }
}