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

inline int read() {
    int x = 0, f = 1;
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

int main() {
    int n = read(), m = read();
    while (m--) {
        int u = read(), v = read(), w = read();
        char op;
        scanf("%c", &op);
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