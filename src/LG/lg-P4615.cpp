#include <cstdio>
#include <iostream>

typedef long long ll;

const int MAX_N = 200050;

struct Node {
    int v;
    int nxt;
} node[MAX_N];

int head[MAX_N];
int cnt;

ll siz[MAX_N], ans[MAX_N];

void create(int u, int v);

void dfs(int x, int f);

template <typename T>
T read();

int main() {
    std::ios::sync_with_stdio(false);

    int n = read<int>();
    for (int i = 1; i < n; i++) {
        int x = read<int>();
        create(x, i + 1);
    }

    dfs(1, 0);
    for (int i = 1; i <= n; i++) {
        std::cout << ans[i] << ' ';
    }
    std::cout << '\n';

    return 0;
}

void create(int u, int v) {
    node[++cnt].v = v;
    node[cnt].nxt = head[u];
    head[u] = cnt;
}

void dfs(int x, int f) {
    siz[x] = 1;
    ans[x] = 0;

    for (int i = head[x]; i; i = node[i].nxt) {
        int v = node[i].v;
        if (v == f) {
            continue;
        }

        dfs(v, x);
        siz[x] += siz[v];
        ans[x] += ans[v];
    }

    ans[x] += siz[x];
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