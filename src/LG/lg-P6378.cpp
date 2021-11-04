#include <algorithm>
#include <cstdio>
#include <iostream>
#include <stack>

const int MAX_N = 4000050;

struct Node {
    int v;
    int nxt;
} node[MAX_N << 2];

int head[MAX_N << 2];
int cnt, idx, tot;

int dfn[MAX_N], low[MAX_N], col[MAX_N];
bool vis[MAX_N];
std::stack<int> stk;

void create(int u, int v);

void tarjan(int x);

template <typename T>
T read();

int main() {
    std::ios::sync_with_stdio(false);

    int n = read<int>(), m = read<int>(), k = read<int>();
    for (int i = 1; i <= m; i++) {
        int x = read<int>(), y = read<int>();
        int a = 1, b = 1;
        create(x + n * (a & 1), y + n * (b ^ 1));
        create(y + n * (b & 1), x + n * (a ^ 1));
    }

    while (k--) {
        int w = read<int>(), p = read<int>();
        create(p, p + n + n);
        create(p + n + n + n, p + n);
        for (int i = 2; i <= w; i++) {
            int x = read<int>();
            create(x, x + n + n);
            create(x + n + n + n, x + n);
            create(p + n + n, x + n + n);
            create(p + n + n, x + n);
            create(x, p + n + n + n);
            create(x + n + n + n, p + n + n + n);
            p = x;
        }
    }

    for (int i = 1; i <= n + n + n + n; i++) {
        if (!dfn[i]) {
            tarjan(i);
        }
    }

    for (int i = 1; i <= n; i++) {
        if (col[i] == col[i + n]) {
            std::cout << "NIE\n";
            return 0;
        }
    }

    std::cout << "TAK\n";

    return 0;
}

void create(int u, int v) {
    node[++cnt].v = v;
    node[cnt].nxt = head[u];
    head[u] = cnt;
}

void tarjan(int x) {
    dfn[x] = low[x] = ++idx;
    vis[x] = true;
    stk.push(x);

    for (int i = head[x]; i; i = node[i].nxt) {
        int v = node[i].v;
        if (!dfn[v]) {
            tarjan(v);
            low[x] = std::min(low[x], low[v]);
        } else if (vis[v]) {
            low[x] = std::min(low[x], low[v]);
        }
    }

    int i = x;
    if (low[x] == dfn[x]) {
        tot++;
        do {
            col[i] = tot;
            i = stk.top();
            stk.pop();
            vis[i] = false;
        } while (i != x);
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