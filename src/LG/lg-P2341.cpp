#include <iostream>
#include <stack>

const int MAX_N = 10050;

struct Node {
    int v;
    int nxt;
} edge[MAX_N * 5];

int head[MAX_N * 5];
int dfn[MAX_N], low[MAX_N], in_deg[MAX_N], ex_deg[MAX_N], num[MAX_N];
bool vis[MAX_N];
int cnt, tot, col;
std::stack<int> s;

void insert(int u, int v);

void tarjan(int x);

int main() {
    std::ios::sync_with_stdio(false);

    int n, m, tmp = 0;
    std::cin >> n >> m;
    for (int i = 1; i <= m; i++) {
        int u, v;
        std::cin >> u >> v;
        insert(u, v);
    }

    for (int i = 1; i <= n; i++) {
        if (!dfn[i]) {
            tarjan(i);
        }
    }
    for (int k = 1; k <= n; k++) {
        for (int i = head[k]; i; i = edge[i].nxt) {
            int u = edge[i].v;
            if (in_deg[k] != in_deg[u]) {
                ex_deg[in_deg[k]]++;
            }
        }
    }

    for (int i = 1; i <= col; i++) {
        if (!ex_deg[i]) {
            if (tmp) {
                std::cout << 0 << '\n';
                return 0;
            }
            tmp = i;
        }
    }
    std::cout << num[tmp] << '\n';

    return 0;
}

void insert(int u, int v) {
    edge[++cnt].v = v;
    edge[cnt].nxt = head[u];
    head[u] = cnt;
}

void tarjan(int x) {
    dfn[x] = low[x] = ++tot;
    vis[x] = true;
    s.push(x);
    for (int i = head[x]; i; i = edge[i].nxt) {
        int u = edge[i].v;
        if (!dfn[u]) {
            tarjan(u);
            low[x] = std::min(low[x], low[u]);
        } else if (vis[u]) {
            low[x] = std::min(low[x], low[u]);
        }
    }
    int k;
    if (low[x] == dfn[x]) {
        ++col;
        do {
            k = s.top();
            s.pop();
            vis[k] = false;
            in_deg[k] = col;
            num[col]++;
        } while (x != k);
    }
}