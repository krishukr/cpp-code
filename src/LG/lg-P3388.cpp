#include <iostream>

const int MAX_N = 100050;

struct Node {
    int v;
    int nxt;
} node[MAX_N << 1];

int head[MAX_N << 1], dfn[MAX_N], low[MAX_N];
bool vis[MAX_N];
int cnt, tot, ans;

void insert(int x, int y);

void tarjan(int x, int y);

int main() {
    std::ios::sync_with_stdio(false);

    int n, m;
    std::cin >> n >> m;
    for (int i = 1; i <= m; i++) {
        int x, y;
        std::cin >> x >> y;
        insert(x, y);
        insert(y, x);
    }

    for (int i = 1; i <= n; i++) {
        if (!dfn[i]) {
            tarjan(i, i);
        }
    }

    for (int i = 1; i <= n; i++) {
        if (vis[i]) {
            ans++;
        }
    }
    std::cout << ans << '\n';
    for (int i = 1; i <= n; i++) {
        if (vis[i]) {
            std::cout << i << ' ';
        }
    }

    return 0;
}

void insert(int x, int y) {
    node[++cnt].v = y;
    node[cnt].nxt = head[x];
    head[x] = cnt;
}

void tarjan(int x, int y) {
    dfn[x] = low[x] = ++tot;
    int tmp = 0;
    for (int i = head[x]; i; i = node[i].nxt) {
        int v = node[i].v;
        if (!dfn[v]) {
            tarjan(v, y);
            low[x] = std::min(low[x], low[v]);
            if (low[v] >= dfn[x] and x != y) {
                vis[x] = true;
            }
            if (x == y) {
                tmp++;
            }
        }
        low[x] = std::min(low[x], dfn[v]);
    }
    if (x == y and tmp >= 2) {
        vis[x] = true;
    }
}