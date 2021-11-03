#include <cstdio>
#include <iostream>

const int MAX_N = 200050;
const int MAX_M = 1000050;

struct Node {
    int v;
    int nxt;
} node[MAX_M];

int head[MAX_M];
int cnt, idx, a, b;

int dfn[MAX_N], low[MAX_N];
bool vis[MAX_N];

void create(int u, int v);

void tarjan(int x);

template <typename T>
T read();

int main() {
    std::ios::sync_with_stdio(false);

    int n = read<int>();
    while (true) {
        int x = read<int>(), y = read<int>();
        if (x == y and x == 0) {
            break;
        }
        create(x, y);
        create(y, x);
    }

    a = read<int>(), b = read<int>();

    // for (int i = 1; i <= n; i++) {
    //     if (!dfn[i]) {
    //         tarjan(i);
    //     }
    // }

    tarjan(a);

    for (int i = 1; i <= n; i++) {
        if (vis[i]) {
            std::cout << i << '\n';
            return 0;
        }
    }

    std::cout << "No solution\n";
    return 0;
}

void create(int u, int v) {
    node[++cnt].v = v;
    node[cnt].nxt = head[u];
    head[u] = cnt;
}

void tarjan(int x) {
    dfn[x] = low[x] = ++idx;
    for (int i = head[x]; i; i = node[i].nxt) {
        int v = node[i].v;
        if (!dfn[v]) {
            tarjan(v);
            low[x] = std::min(low[x], low[v]);

            if (low[v] >= dfn[x] and x != a and dfn[b] >= dfn[v]) {
                vis[x] = true;
            }
        } else {
            low[x] = std::min(low[x], dfn[v]);
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