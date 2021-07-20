#include <climits>
#include <cstdio>
#include <cstring>
#include <iostream>

const int MAX_N = 400050;

namespace Star {

struct Edge {
    int v;
    int w;  // value
    int nxt;
} node[MAX_N];

int head[MAX_N];
int cnt;

void create(int u, int v, int w);

}  // namespace Star

namespace Tree {

struct Tree {
    int l;
    int r;
    int s;  // sum
    int t;  // tag
    int max;
    int min;
} tree[MAX_N << 2];

void update(int x);

void pushdown(int x);

void build(int x, int l, int r);

void mod(int x, int p, int k);

void reverse(int x, int l, int r);

int sum(int x, int l, int r);

int max(int x, int l, int r);

int min(int x, int l, int r);

}  // namespace Tree

namespace HLD {

struct Que {
    int x;
    int y;
} id[MAX_N];

int fa[MAX_N], son[MAX_N], top[MAX_N], dep[MAX_N], dfn[MAX_N], siz[MAX_N],
    tmp[MAX_N], w[MAX_N];
int idx;

void dfs1(int x, int f);

void dfs2(int x, int t);

void mod(int x, int y);

int sum(int x, int y);

int max(int x, int y);

int min(int x, int y);

}  // namespace HLD

template <typename T>
T read();

int main() {
    // std::ios::sync_with_stdio(false);
    // freopen("lg-P1505.in", "r", stdin);
    // freopen("lg-P1505.out", "w", stdout);

    int n = read<int>();
    for (int i = 1; i < n; i++) {
        int u = read<int>() + 1;
        int v = read<int>() + 1;
        int w = read<int>();

        Star::create(u, v, w);
        Star::create(v, u, w);

        HLD::id[i].x = u;
        HLD::id[i].y = v;
    }

    HLD::dfs1(1, 0);
    HLD::dfs2(1, 1);
    Tree::build(1, 1, n);

    int m = read<int>();
    for (int kkk = 1; kkk <= m; kkk++) {
        std::string s;
        std::cin >> s;
        int x = read<int>(), y = read<int>();

        if (s == "C") {
            using HLD::dfn;
            using HLD::fa;
            using HLD::id;

            if (fa[id[x].x] == id[x].y) {
                Tree::mod(1, dfn[id[x].x], y);
            } else {
                Tree::mod(1, dfn[id[x].y], y);
            }
        }

        if (s == "N") {
            HLD::mod(x + 1, y + 1);
        }
        if (s == "SUM") {
            std::cout << HLD::sum(x + 1, y + 1) << '\n';
        }
        if (s == "MAX") {
            std::cout << HLD::max(x + 1, y + 1) << '\n';
        }
        if (s == "MIN") {
            std::cout << HLD::min(x + 1, y + 1) << '\n';
        }
    }

    return 0;
}

namespace Star {

void create(int u, int v, int w) {
    node[++cnt].v = v;
    node[cnt].w = w;
    node[cnt].nxt = head[u];
    head[u] = cnt;
}

}  // namespace Star

namespace Tree {

void update(int x) {
    tree[x].s = tree[x * 2].s + tree[x * 2 + 1].s;
    tree[x].max = std::max(tree[x * 2].max, tree[x * 2 + 1].max);
    tree[x].min = std::min(tree[x * 2].min, tree[x * 2 + 1].min);
}

void pushdown(int x) {
    if (tree[x].t) {
        tree[x * 2].t ^= 1;
        tree[x * 2 + 1].t ^= 1;
        tree[x * 2].s = -tree[x * 2].s;
        tree[x * 2 + 1].s = -tree[x * 2 + 1].s;
        tree[x * 2].max = -tree[x * 2].max;
        tree[x * 2 + 1].max = -tree[x * 2 + 1].max;
        tree[x * 2].min = -tree[x * 2].min;
        tree[x * 2 + 1].min = -tree[x * 2 + 1].min;

        std::swap(tree[x * 2].max, tree[x * 2].min);
        std::swap(tree[x * 2 + 1].max, tree[x * 2 + 1].min);
        tree[x].t = 0;
    }
}

void build(int x, int l, int r) {
    tree[x].l = l;
    tree[x].r = r;

    if (l == r) {
        tree[x].min = tree[x].max = tree[x].s = HLD::w[l];
    } else {
        int mid = (tree[x].l + tree[x].r) / 2;
        build(x * 2, l, mid);
        build(x * 2 + 1, mid + 1, r);
        update(x);
    }
}

void mod(int x, int p, int k) {
    if (tree[x].l == tree[x].r) {
        tree[x].max = tree[x].min = tree[x].s = k;
    } else {
        pushdown(x);
        int mid = (tree[x].l + tree[x].r) / 2;
        if (p <= mid) {
            mod(x * 2, p, k);
        } else {
            mod(x * 2 + 1, p, k);
        }
        update(x);
    }
}

void reverse(int x, int l, int r) {
    if (l <= tree[x].l and tree[x].r <= r) {
        tree[x].t ^= 1;
        tree[x].min = -tree[x].min;
        tree[x].max = -tree[x].max;
        tree[x].s = -tree[x].s;
        std::swap(tree[x].max, tree[x].min);
    } else {
        pushdown(x);
        int mid = (tree[x].l + tree[x].r) / 2;
        if (l <= mid) {
            reverse(x * 2, l, r);
        }
        if (mid < r) {
            reverse(x * 2 + 1, l, r);
        }
        update(x);
    }
}

int sum(int x, int l, int r) {
    if (l <= tree[x].l and tree[x].r <= r) {
        return tree[x].s;
    } else {
        pushdown(x);
        int res = 0;
        int mid = (tree[x].l + tree[x].r) / 2;
        if (l <= mid) {
            res += sum(x * 2, l, r);
        }
        if (mid < r) {
            res += sum(x * 2 + 1, l, r);
        }
        update(x);
        return res;
    }
}

int max(int x, int l, int r) {
    if (l <= tree[x].l and tree[x].r <= r) {
        return tree[x].max;
    } else {
        pushdown(x);
        int res = INT_MIN;
        int mid = (tree[x].l + tree[x].r) / 2;
        if (l <= mid) {
            res = std::max(res, max(x * 2, l, r));
        }
        if (mid < r) {
            res = std::max(res, max(x * 2 + 1, l, r));
        }
        update(x);
        return res;
    }
}

int min(int x, int l, int r) {
    if (l <= tree[x].l and tree[x].r <= r) {
        return tree[x].min;
    } else {
        pushdown(x);
        int res = INT_MAX;
        int mid = (tree[x].l + tree[x].r) / 2;
        if (l <= mid) {
            res = std::min(res, min(x * 2, l, r));
        }
        if (mid < r) {
            res = std::min(res, min(x * 2 + 1, l, r));
        }
        update(x);
        return res;
    }
}

}  // namespace Tree

namespace HLD {

void dfs1(int x, int f) {
    using Star::head;
    using Star::node;

    dep[x] = dep[f] + 1;
    fa[x] = f;
    siz[x] = 1;

    for (int i = head[x]; i; i = node[i].nxt) {
        int v = node[i].v;
        if (v == f) {
            continue;
        }
        tmp[v] = node[i].w;
        dfs1(v, x);
        siz[x] += siz[v];

        if (siz[son[x]] < siz[v]) {
            son[x] = v;
        }
    }
}

void dfs2(int x, int t) {
    using Star::head;
    using Star::node;

    dfn[x] = ++idx;
    w[idx] = tmp[x];
    top[x] = t;

    if (son[x]) {
        dfs2(son[x], t);
    }
    for (int i = head[x]; i; i = node[i].nxt) {
        int v = node[i].v;
        if (v == fa[x] or v == son[x]) {
            continue;
        }
        dfs2(v, v);
    }
}

void mod(int x, int y) {
    while (top[x] != top[y]) {
        if (dep[top[x]] < dep[top[y]]) {
            std::swap(x, y);
        }
        Tree::reverse(1, dfn[top[x]], dfn[x]);
        x = fa[top[x]];
    }
    if (dep[x] > dep[y]) {
        std::swap(x, y);
    }
    if (x != y) {
        Tree::reverse(1, dfn[x] + 1, dfn[y]);
    }
}

int sum(int x, int y) {
    int res = 0;
    while (top[x] != top[y]) {
        if (dep[top[x]] < dep[top[y]]) {
            std::swap(x, y);
        }
        res += Tree::sum(1, dfn[top[x]], dfn[x]);
        x = fa[top[x]];
    }
    if (dep[x] > dep[y]) {
        std::swap(x, y);
    }
    if (x != y) {
        res += Tree::sum(1, dfn[x] + 1, dfn[y]);
    }
    return res;
}

int max(int x, int y) {
    int res = INT_MIN;
    while (top[x] != top[y]) {
        if (dep[top[x]] < dep[top[y]]) {
            std::swap(x, y);
        }
        res = std::max(res, Tree::max(1, dfn[top[x]], dfn[x]));
        x = fa[top[x]];
    }
    if (dep[x] > dep[y]) {
        std::swap(x, y);
    }
    if (x != y) {
        res = std::max(res, Tree::max(1, dfn[x] + 1, dfn[y]));
    }
    return res;
}

int min(int x, int y) {
    int res = INT_MAX;
    while (top[x] != top[y]) {
        if (dep[top[x]] < dep[top[y]]) {
            std::swap(x, y);
        }
        res = std::min(res, Tree::min(1, dfn[top[x]], dfn[x]));
        x = fa[top[x]];
    }
    if (dep[x] > dep[y]) {
        std::swap(x, y);
    }
    if (x != y) {
        res = std::min(res, Tree::min(1, dfn[x] + 1, dfn[y]));
    }
    return res;
}

}  // namespace HLD

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