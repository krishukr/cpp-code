#include <algorithm>
#include <cstdio>
#include <iostream>

const int MAX_N = 1000050;

struct Node {
    int v;
    int nxt;
} node[MAX_N];

int head[MAX_N];
int cnt;

struct Tree {
    int lc;
    int rc;
    int sum;
} tree[MAX_N << 2];

int a[MAX_N], b[MAX_N];
int tot, mm;

int fa[MAX_N][30], dep[MAX_N], son[MAX_N];

#pragma region initial
void create(int u, int v);

void dfs1(int x, int d);

void dfs2(int x);

namespace TreeOp {

int mod(int p, int l, int r, int v);

int query(int x, int y, int z, int w, int l, int r, int k);

}  // namespace TreeOp

int solve(int x, int y);

template <typename T>
T read();
#pragma endregion initial

int main() {
    std::ios::sync_with_stdio(false);
    // freopen("lg-P2633.in", "r", stdin);
    // freopen("lg-P2633.out", "w", stdout);

    int n = read<int>(), m = read<int>();
    for (int i = 1; i <= n; i++) {
        a[i] = read<int>();
        b[i] = a[i];
    }
    std::sort(b + 1, b + n + 1);
    mm = std::unique(b + 1, b + n + 1) - b - 1;

    for (int i = 1; i < n; i++) {
        int x = read<int>(), y = read<int>();
        create(x, y);
        create(y, x);
    }
    dfs1(1, 0);
    dfs2(1);

    int last = 0;
    for (int i = 1; i <= m; i++) {
        int u = read<int>() ^ last;
        int v = read<int>(), w = read<int>();
        int z = solve(u, v);

        last =
            b[TreeOp::query(son[u], son[v], son[z], son[fa[z][0]], 1, mm, w)];

        std::cout << last << '\n';
    }

    return 0;
}

void create(int u, int v) {
    node[++cnt].v = v;
    node[cnt].nxt = head[u];
    head[u] = cnt;
}

void dfs1(int x, int d) {
    dep[x] = d;
    for (int i = 1; i <= 19; i++) {
        fa[x][i] = fa[fa[x][i - 1]][i - 1];
    }
    for (int i = head[x]; i; i = node[i].nxt) {
        int v = node[i].v;
        if (v == fa[x][0]) {
            continue;
        }
        fa[v][0] = x;
        dfs1(v, d + 1);
    }
}

void dfs2(int x) {
    son[x] = TreeOp::mod(son[fa[x][0]], 1, mm,
                         std::lower_bound(b + 1, b + mm + 1, a[x]) - b);
    for (int i = head[x]; i; i = node[i].nxt) {
        int v = node[i].v;
        if (v == fa[x][0]) {
            continue;
        }
        dfs2(v);
    }
}

namespace TreeOp {

int mod(int p, int l, int r, int v) {
    int x = ++cnt;
    tree[x] = tree[p];
    tree[x].sum++;
    int mid = (l + r) / 2;
    if (l < r) {
        if (v <= mid) {
            tree[x].lc = mod(tree[p].lc, l, mid, v);
        } else {
            tree[x].rc = mod(tree[p].rc, mid + 1, r, v);
        }
    }
    return x;
}

int query(int x, int y, int z, int w, int l, int r, int k) {
    if (l == r) {
        return l;
    }
    int sum = tree[tree[x].lc].sum + tree[tree[y].lc].sum -
              tree[tree[z].lc].sum - tree[tree[w].lc].sum;
    int mid = (l + r) / 2;
    if (sum >= k) {
        return query(tree[x].lc, tree[y].lc, tree[z].lc, tree[w].lc, l, mid, k);
    } else {
        return query(tree[x].rc, tree[y].rc, tree[z].rc, tree[w].rc, mid + 1, r,
                     k - sum);
    }
}

}  // namespace TreeOp

int solve(int x, int y) {
    if (dep[x] > dep[y]) {
        std::swap(x, y);
    }
    for (int d = dep[y] - dep[x], i = 0; d; d /= 2, i++) {
        if (d & 1) {
            y = fa[y][i];
        }
    }
    if (x == y) {
        return x;
    }

    for (int i = 19; i >= 0; i--) {
        if (fa[x][i] != fa[y][i]) {
            x = fa[x][i];
            y = fa[y][i];
        }
    }
    return fa[x][0];
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