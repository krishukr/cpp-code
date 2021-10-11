#include <cstdio>
#include <iostream>
#include <queue>

const int MAX_N = 2000000;
const int MOD = 100003;

struct Node {
    int v;
    int nxt;
} node[MAX_N];

int head[MAX_N], dep[MAX_N], ans[MAX_N];
bool vis[MAX_N];
int cnt;

void create(int u, int v);

template <typename T>
T read();

int main() {
    std::ios::sync_with_stdio(false);

    int n = read<int>(), m = read<int>();
    for (int i = 1; i <= m; i++) {
        int x = read<int>(), y = read<int>();
        create(x, y);
        create(y, x);
    }

    std::queue<int> q;
    q.push(1);
    vis[1] = true;
    ans[1] = 1;

    while (!q.empty()) {
        int p = q.front();
        q.pop();

        for (int i = head[p]; i; i = node[i].nxt) {
            int v = node[i].v;
            if (!vis[v]) {
                q.push(v);
                vis[v] = true;
                dep[v] = dep[p] + 1;
            }
            if (dep[v] == dep[p] + 1) {
                ans[v] += ans[p];
                ans[v] %= MOD;
            }
        }
    }

    for (int i = 1; i <= n; i++) {
        std::cout << ans[i] << '\n';
    }

    return 0;
}

void create(int u, int v) {
    node[++cnt].v = v;
    node[cnt].nxt = head[u];
    head[u] = cnt;
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