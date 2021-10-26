#include <cstdio>
#include <cstring>
#include <iostream>
#include <map>
#include <stack>

const int MAX_N = 50050;

struct Node {
    int v;
    int nxt;
} node[MAX_N];

int head[MAX_N];
int cnt, idx, col;
int dfn[MAX_N], low[MAX_N], fa[MAX_N];
bool vis[MAX_N];

std::map<std::string, int> cp;
std::stack<int> stk;

void create(int u, int v);

void tarjan(int x);

template <typename T>
T read();

int main() {
    // std::ios::sync_with_stdio(false);

    int n = read<int>();
    for (int i = 1; i <= n; i++) {
        std::string g, b;
        std::cin >> g >> b;

        cp[g] = i;
        cp[b] = i + n;
        create(i, i + n);
    }

    int m = read<int>();
    for (int i = 1; i <= m; i++) {
        std::string g, b;
        std::cin >> g >> b;
        create(cp[b], cp[g]);
    }

    for (int i = 1; i <= n + n; i++) {
        if (!dfn[i]) {
            tarjan(i);
        }
    }

    for (int i = 1; i <= n; i++) {
        if (fa[i] == fa[i + n]) {
            std::cout << "Unsafe\n";
        } else {
            std::cout << "Safe\n";
        }
    }

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
        } while (k != x);
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