#include <algorithm>
#include <cstdio>
#include <iostream>
#include <stack>

const int MAX_N = 2000050;

struct Node {
    int v;
    int nxt;
} node[MAX_N];

int head[MAX_N];
int cnt;

int v[MAX_N], min[MAX_N], ind[MAX_N];

int col[MAX_N], dfn[MAX_N], low[MAX_N];
bool vis[MAX_N];
int idx, num;
std::stack<int> stk;

void create(int u, int v);

void tarjan(int x);

template <typename T>
T read();

int main() {
    std::ios::sync_with_stdio(false);

    int n = read<int>(), m = read<int>(), k = read<int>();

    for (int i = 1; i <= n; i++) {
        v[i] = read<int>();
    }
    v[0] = 0x3f3f3f3f;

    for (int i = 1; i <= m; i++) {
        int x = read<int>(), y = read<int>();
        create(x, y);
    }

    for (int i = 1; i <= n; i++) {
        if (!dfn[i]) {
            tarjan(i);
        }
    }

    for (int i = 1; i <= n; i++) {
        for (int j = head[i]; j; j = node[j].nxt) {
            int v = node[j].v;
            if (col[v] != col[i]) {
                ind[col[v]]++;
            }
        }
    }

    for (int i = 1; i <= num; i++) {
        if (!ind[i]) {
            v[min[i]] = 0;
        }
    }
    std::sort(v + 1, v + n + 1,
              [](const int &a, const int &b) -> bool { return a > b; });

    int ans = 0;
    for (int i = 1; i <= k; i++) {
        ans += v[i];
    }
    std::cout << ans << '\n';

    return 0;
}

void create(int u, int v) {
    node[++cnt].v = v;
    node[cnt].nxt = head[u];
    head[u] = cnt;
}

void tarjan(int x) {
    low[x] = dfn[x] = ++idx;
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

    if (low[x] == dfn[x]) {
        int k;
        num++;
        do {
            k = stk.top();
            stk.pop();
            vis[k] = false;
            col[k] = num;
            if (v[k] < v[min[num]]) {
                min[num] = k;
            }
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