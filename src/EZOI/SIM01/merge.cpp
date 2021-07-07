#include <iostream>

const int MAX_N = 1000050;

struct Node {
    int v;
    int nxt;
} node[MAX_N];

int head[MAX_N], fa[MAX_N], ans[MAX_N];
bool vis[MAX_N];
int tot, cnt;

inline int read();

void init(int n);

int find(int x);

void merge(int i, int j);

void create(int x, int y);

void dfs(int n);

int main() {
    std::ios::sync_with_stdio(false);

    int n = read(), q = read();
    init(n);
    cnt = n;

    while (q--) {
        int op = read(), x = read(), y = read();
        if (op == 1) {
            if (find(x) == find(y)) {
                continue;
            } else {
                cnt++;
                fa[cnt] = cnt;
                create(cnt, find(x));
                create(cnt, find(y));
            }
        } else {
            ans[find(x)] += y;
        }
    }

    for (int i = 1; i <= cnt; i++) {
        if (!vis[i]) {
            dfs(find(i));
        }
    }
    for (int i = 1; i <= n; i++) {
        std::cout << ans[i] << ' ';
    }

    return 0;
}

inline int read() {
    int x = 0, f = 1;
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

void init(int n) {
    for (int i = 1; i <= n; i++) {
        fa[i] = i;
    }
}

int find(int x) { return x == fa[x] ? x : (fa[x] = find(fa[x])); }

void merge(int i, int j) { fa[find(i)] = find(j); }

void create(int x, int y) {
    node[++tot].v = y;
    node[tot].nxt = head[x];
    head[x] = tot;
    fa[find(y)] = fa[find(x)];
}

void dfs(int n) {
    vis[n] = true;
    for (int i = head[n]; i; i = node[i].nxt) {
        ans[node[i].v] += ans[n];
        dfs(node[i].v);
    }
}