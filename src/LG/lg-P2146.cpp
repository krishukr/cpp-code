#include <cmath>
#include <cstdio>
#include <iostream>

const int MAX_N = 2000050;

namespace Star {

struct Node {
    int v;
    int nxt;
} node[MAX_N];

int head[MAX_N];
int cnt;

void create(int u, int v);

}  // namespace Star

namespace Tree {

struct Node {
    int l;
    int r;
    int s;  // sum
    int t;  // tag
} tree[MAX_N];

void update(int x);

void pushdown(int x);

void build(int x, int l, int r);

void mod(int x, int l, int r, int v);

}  // namespace Tree

namespace HLD {

int fa[MAX_N], son[MAX_N], top[MAX_N], dep[MAX_N], dfn[MAX_N], siz[MAX_N],
    tmp[MAX_N], w[MAX_N];
int idx;

void dfs1(int x, int f);

void dfs2(int x, int t);

void mod(int x, int y);

}  // namespace HLD

template <typename T>
T read();

int main() {
    // std::ios::sync_with_stdio(false);

    int n = read<int>();
    for (int i = 1; i < n; i++) {
        int x = read<int>();
        Star::create(x + 1, i + 1);
    }

    HLD::dfs1(1, 0);
    HLD::dfs2(1, 1);
    Tree::build(1, 1, HLD::idx);

    int q = read<int>();
    for (int kkk = 1; kkk <= q; kkk++) {
        std::string s;
        std::cin >> s;
        int x = read<int>() + 1;
        int v = Tree::tree[1].s;

        if (s == "install") {
            HLD::mod(1, x);
            std::cout << std::abs(Tree::tree[1].s - v) << '\n';
        }
        if (s == "uninstall") {
            using HLD::dfn;

            Tree::mod(1, dfn[x], dfn[x] + HLD::siz[x] - 1, 0);
            std::cout << std::abs(Tree::tree[1].s - v) << '\n';
        }
    }

    return 0;
}

namespace Star {

void create(int u, int v) {
    node[++cnt].v = v;
    node[cnt].nxt = head[u];
    head[u] = cnt;
}

}  // namespace Star

namespace Tree {

void update(int x) { tree[x].s = tree[x * 2].s + tree[x * 2 + 1].s; }

void pushdown(int x) {
    if (tree[x].t != -1) {
        tree[x * 2].s = (tree[x * 2].r - tree[x * 2].l + 1) * tree[x].t;
        tree[x * 2 + 1].s =
            (tree[x * 2 + 1].r - tree[x * 2 + 1].l + 1) * tree[x].t;
        tree[x * 2].t = tree[x].t;
        tree[x * 2 + 1].t = tree[x].t;
        tree[x].t = -1;
    }
}

void build(int x, int l, int r) {
    tree[x].l = l;
    tree[x].r = r;
    tree[x].t = -1;

    if (l == r) {
        return;
    } else {
        int mid = (tree[x].l + tree[x].r) / 2;
        build(x * 2, l, mid);
        build(x * 2 + 1, mid + 1, r);
        update(x);
    }
}

void mod(int x, int l, int r, int v) {
    if (tree[x].r < l or tree[x].l > r) {
        return;
    }
    if (l <= tree[x].l and tree[x].r <= r) {
        tree[x].t = v;
        tree[x].s = (tree[x].r - tree[x].l + 1) * v;
    } else {
        pushdown(x);
        int mid = (tree[x].l + tree[x].r) / 2;
        mod(x * 2, l, r, v);
        mod(x * 2 + 1, l, r, v);
        update(x);
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
        Tree::mod(1, dfn[top[x]], dfn[x], 1);
        x = fa[top[x]];
    }
    if (dep[x] > dep[y]) {
        std::swap(x, y);
    }
    Tree::mod(1, dfn[x], dfn[y], 1);
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