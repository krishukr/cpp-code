#include <cstdio>
#include <iostream>

const int MAX_N = 1000050;
int MOD;

struct Node {
    int v;
    int nxt;
} node[MAX_N];

int head[MAX_N];
int cnt;

struct Tree {
    int l;
    int r;
    int w;
    int size;
    int tag;
} tree[MAX_N << 1];

int a[MAX_N], b[MAX_N];
int dep[MAX_N], fa[MAX_N], son[MAX_N], tot[MAX_N], top[MAX_N], idx[MAX_N];

#pragma region initial
void create(int u, int v);

int dfs1(int x, int f, int d);

void dfs2(int x, int t);

void update(int x);

void pushdown(int x);

void build(int x, int l, int r);

void mod(int x, int l, int r, int v);

void add(int x, int y, int v);

int sum(int x, int l, int r);

int query(int x, int y);

template <typename T>
T read();
#pragma endregion initial

signed main() {
    std::ios::sync_with_stdio(false);

    int n = read<int>(), m = read<int>(), r = read<int>();
    MOD = read<int>();
    for (int i = 1; i <= n; i++) {
        b[i] = read<int>();
    }
    for (int i = 1; i < n; i++) {
        int x = read<int>(), y = read<int>();
        create(x, y);
        create(y, x);
    }
    cnt = 0;
    dfs1(r, 0, 1);
    dfs2(r, r);
    build(1, 1, n);

    while (m--) {
        int op = read<int>();
        if (op == 1) {
            int x = read<int>(), y = read<int>(), z = read<int>();
            z %= MOD;
            add(x, y, z);
        }
        if (op == 2) {
            int x = read<int>(), y = read<int>();
            std::cout << query(x, y) << '\n';
        }
        if (op == 3) {
            int x = read<int>(), z = read<int>();
            z %= MOD;
            mod(1, idx[x], idx[x] + tot[x] - 1, z);
        }
        if (op == 4) {
            int x = read<int>();
            std::cout << sum(1, idx[x], idx[x] + tot[x] - 1) << '\n';
        }
    }

    return 0;
}

void create(int u, int v) {
    node[++cnt].v = v;
    node[cnt].nxt = head[u];
    head[u] = cnt;
}

int dfs1(int x, int f, int d) {
    dep[x] = d;
    fa[x] = f;
    tot[x] = 1;
    int res = -1;
    for (int i = head[x]; i; i = node[i].nxt) {
        int v = node[i].v;
        if (v == f) {
            continue;
        }
        tot[x] += dfs1(v, x, d + 1);
        if (tot[v] > res) {
            res = tot[v];
            son[x] = v;
        }
    }
    return tot[x];
}

void dfs2(int x, int t) {
    idx[x] = ++cnt;
    a[cnt] = b[x];
    top[x] = t;
    if (!son[x]) {
        return;
    } else {
        dfs2(son[x], t);
        for (int i = head[x]; i; i = node[i].nxt) {
            int v = node[i].v;
            if (!idx[v]) {
                dfs2(v, v);
            }
        }
    }
}

void update(int x) {
    tree[x].w = (tree[x * 2].w + tree[x * 2 + 1].w + MOD) % MOD;
}

void pushdown(int x) {
    if (!tree[x].tag) {
        return;
    } else {
        tree[x * 2].w = (tree[x * 2].w + tree[x * 2].size * tree[x].tag) % MOD;
        tree[x * 2 + 1].w =
            (tree[x * 2 + 1].w + tree[x * 2 + 1].size * tree[x].tag) % MOD;
        tree[x * 2].tag = (tree[x * 2].tag + tree[x].tag) % MOD;
        tree[x * 2 + 1].tag = (tree[x * 2 + 1].tag + tree[x].tag) % MOD;
        tree[x].tag = 0;
    }
}

void build(int x, int l, int r) {
    tree[x].l = l;
    tree[x].r = r;
    tree[x].size = r - l + 1;

    if (l == r) {
        tree[x].w = a[l];
        return;
    } else {
        int mid = (l + r) / 2;
        build(x * 2, l, mid);
        build(x * 2 + 1, mid + 1, r);
        update(x);
    }
}

void mod(int x, int l, int r, int v) {
    if (l <= tree[x].l and tree[x].r <= r) {
        tree[x].w += tree[x].size * v;
        tree[x].tag += v;
        return;
    } else {
        pushdown(x);
        int mid = (tree[x].l + tree[x].r) / 2;
        if (l <= mid) {
            mod(x * 2, l, r, v);
        }
        if (r > mid) {
            mod(x * 2 + 1, l, r, v);
        }
        update(x);
    }
}

void add(int x, int y, int v) {
    while (top[x] != top[y]) {
        if (dep[top[x]] < dep[top[y]]) {
            std::swap(x, y);
        }
        mod(1, idx[top[x]], idx[x], v);
        x = fa[top[x]];
    }
    if (dep[x] > dep[y]) {
        std::swap(x, y);
    }
    mod(1, idx[x], idx[y], v);
}

int sum(int x, int l, int r) {
    if (l <= tree[x].l and tree[x].r <= r) {
        return tree[x].w;
    } else {
        pushdown(x);
        int mid = (tree[x].l + tree[x].r) / 2, ans = 0;
        if (l <= mid) {
            ans += sum(x * 2, l, r);
            ans %= MOD;
        }
        if (r > mid) {
            ans += sum(x * 2 + 1, l, r);
            ans %= MOD;
        }
        return ans;
    }
}

int query(int x, int y) {
    int ans = 0;
    while (top[x] != top[y]) {
        if (dep[top[x]] < dep[top[y]]) {
            std::swap(x, y);
        }
        ans += sum(1, idx[top[x]], idx[x]);
        ans %= MOD;
        x = fa[top[x]];
    }
    if (dep[x] > dep[y]) {
        std::swap(x, y);
    }
    ans += sum(1, idx[x], idx[y]);
    ans %= MOD;
    return ans;
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