#include <algorithm>
#include <cstdio>
#include <iostream>

const int MAX_N = 5000050;

struct Node {
    int v;
    int nxt;
} node[MAX_N];

int head[MAX_N], v[MAX_N], w[MAX_N], a[MAX_N];
int cnt, n, m, ans;

void create(int u, int v);

void dfs(int x);

template <typename T>
T read();

int main() {
    std::ios::sync_with_stdio(false);

    n = read<int>(), m = read<int>();
    for (int i = 1; i <= n; i++) {
        v[i] = read<int>();
    }

    for (int i = 1; i <= n; i++) {
        int t = read<int>();
        w[i] = t + v[i];
        for (int j = 1; j <= t; j++) {
            int x = read<int>();
            create(i, x + 1);
        }
    }

    dfs(1);
    std::cout << ans << '\n';

    return 0;
}

void dfs(int x) {
    for (int i = head[x]; i; i = node[i].nxt) {
        int v = node[i].v;
        dfs(v);
    }

    int tot = 0;
    for (int i = head[x]; i; i = node[i].nxt) {
        int v = node[i].v;
        a[++tot] = w[v];
    }
    std::sort(a + 1, a + tot + 1);

    for (int i = 1; i <= tot; i++) {
        if (w[x] + a[i] - 1 <= m) {
            w[x] += a[i] - 1;
            ans++;
        } else {
            break;
        }
    }
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