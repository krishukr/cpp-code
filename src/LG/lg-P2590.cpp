#include <climits>
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
    int l;
    int r;
    int w;  // value
    int m;  // max
    int size;
} tree[MAX_N << 1];

int a[MAX_N], b[MAX_N];
int dep[MAX_N], fa[MAX_N], son[MAX_N], tot[MAX_N], top[MAX_N], idx[MAX_N];

#pragma region initial

void create(int u, int v);

int dfs1(int x, int f, int d);

void dfs2(int x, int t);

namespace TreeOperate {

void update(int x);

void build(int x, int l, int r);

void mod(int x, int k, int v);

int sum(int x, int l, int r);

int max(int x, int l, int r);

}  // namespace TreeOperate

int sum(int x, int y);

int max(int x, int y);

template <typename T>
T read();
#pragma endregion initial

int main() {
    // std::ios::sync_with_stdio(false);

    int n = read<int>();
    for (int i = 1; i < n; i++) {
        int x = read<int>(), y = read<int>();
        create(x, y);
        create(y, x);
    }
    for (int i = 1; i <= n; i++) {
        b[i] = read<int>();
    }

    dfs1(1, 0, 1);
    cnt = 0;
    dfs2(1, 1);
    TreeOperate::build(1, 1, n);

    int q = read<int>();
    while (q--) {
        std::string s;
        std::cin >> s;
        int x = read<int>(), y = read<int>();

        if (s == "CHANGE") {
            TreeOperate::mod(1, idx[x], y);
        }
        if (s == "QMAX") {
            std::cout << max(x, y) << '\n';
        }
        if (s == "QSUM") {
            std::cout << sum(x, y) << '\n';
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

namespace TreeOperate {

void update(int x) {
    tree[x].w = tree[x * 2].w + tree[x * 2 + 1].w;
    tree[x].m = std::max(tree[x * 2].m, tree[x * 2 + 1].m);
}

void build(int x, int l, int r) {
    tree[x].l = l;
    tree[x].r = r;
    tree[x].size = r - l + 1;

    if (l == r) {
        tree[x].w = tree[x].m = a[l];
        return;
    } else {
        int mid = (l + r) / 2;
        build(x * 2, l, mid);
        build(x * 2 + 1, mid + 1, r);
        update(x);
    }
}

void mod(int x, int k, int v) {
    if (tree[x].l == tree[x].r) {
        tree[x].w = tree[x].m = v;
    } else {
        int mid = (tree[x].l + tree[x].r) / 2;
        if (k <= mid) {
            mod(x * 2, k, v);
        } else {
            mod(x * 2 + 1, k, v);
        }
        update(x);
    }
}

int sum(int x, int l, int r) {
    if (l <= tree[x].l and tree[x].r <= r) {
        return tree[x].w;
    } else {
        int mid = (tree[x].l + tree[x].r) / 2, ans = 0;
        if (l <= mid) {
            ans += sum(x * 2, l, r);
        }
        if (r > mid) {
            ans += sum(x * 2 + 1, l, r);
        }
        return ans;
    }
}

int max(int x, int l, int r) {
    if (l <= tree[x].l and tree[x].r <= r) {
        return tree[x].m;
    } else {
        int mid = (tree[x].l + tree[x].r) / 2, ans = INT_MIN;
        if (l <= mid) {
            ans = std::max(ans, TreeOperate::max(x * 2, l, r));
        }
        if (r > mid) {
            ans = std::max(ans, TreeOperate::max(x * 2 + 1, l, r));
        }
        return ans;
    }
}

}  // namespace TreeOperate

int sum(int x, int y) {
    int ans = 0;
    while (top[x] != top[y]) {
        if (dep[top[x]] < dep[top[y]]) {
            std::swap(x, y);
        }
        ans += TreeOperate::sum(1, idx[top[x]], idx[x]);
        x = fa[top[x]];
    }
    if (dep[x] > dep[y]) {
        std::swap(x, y);
    }
    ans += TreeOperate::sum(1, idx[x], idx[y]);
    return ans;
}

int max(int x, int y) {
    int ans = INT_MIN;
    while (top[x] != top[y]) {
        if (dep[top[x]] < dep[top[y]]) {
            std::swap(x, y);
        }
        ans = std::max(ans, TreeOperate::max(1, idx[top[x]], idx[x]));
        x = fa[top[x]];
    }
    if (dep[x] > dep[y]) {
        std::swap(x, y);
    }
    ans = std::max(ans, TreeOperate::max(1, idx[x], idx[y]));
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