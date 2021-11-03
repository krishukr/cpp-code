#include <cstdio>
#include <iostream>
#include <vector>

const int MAX_N = 100050;
const int MAX_M = 2000050;

struct Node {
    int v;
    int nxt;
} node[MAX_M];

int head[MAX_M];
int cnt, idx;
int n, m, k, l;

int a[MAX_N], b[MAX_N];
int dfn[MAX_N], low[MAX_N];

std::vector<std::pair<int, int>> ans;

void create(int u, int v);

void dfs(int x, int f);

template <typename T>
T read();

int main() {
    std::ios::sync_with_stdio(false);

    n = read<int>(), m = read<int>(), k = read<int>(), l = read<int>();
    for (int i = 1; i <= k; i++) {
        int x = read<int>();
        a[x]++;
    }
    for (int i = 1; i <= l; i++) {
        int x = read<int>();
        b[x]++;
    }

    for (int i = 1; i <= m; i++) {
        int x = read<int>(), y = read<int>();
        create(x, y);
        create(y, x);
    }

    for (int i = 1; i <= n; i++) {
        if (!dfn[i]) {
            dfs(i, 0);
        }
    }

    std::cout << ans.size() << '\n';
    for (auto i : ans) {
        std::cout << i.first << ' ' << i.second << '\n';
    }

    return 0;
}

void create(int u, int v) {
    node[++cnt].v = v;
    node[cnt].nxt = head[u];
    head[u] = cnt;
}

void dfs(int x, int f) {
    dfn[x] = low[x] = ++idx;
    for (int i = head[x]; i; i = node[i].nxt) {
        int v = node[i].v;
        if (!dfn[v]) {
            dfs(v, x);
            low[x] = std::min(low[x], low[v]);

            a[x] += a[v];
            b[x] += b[v];

            if (low[v] > dfn[x]) {
                if (!a[v] or !b[v] or a[v] == k or b[v] == l) {
                    ans.push_back(std::make_pair(x, v));
                }
            }
        }
        if (v != f) {
            low[x] = std::min(low[x], low[v]);
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