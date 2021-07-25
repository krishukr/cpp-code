#include <cstdio>
#include <iostream>

const int MAX_N = 800050;

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
    int t;   // tag
    int c;   // color
    int lc;  // left child color
    int rc;  // right child color
} tree[MAX_N << 2];

int lc, rc;

void update(int x);

void pushdown(int x);

void build(int x, int l, int r);

void mod(int x, int l, int r, int v);

int query(int x, int l, int r);

}  // namespace Tree

namespace HLD {

int fa[MAX_N], son[MAX_N], top[MAX_N], dep[MAX_N], dfn[MAX_N], siz[MAX_N],
    w[MAX_N];
int idx;

int p1, p2;

void dfs1(int x, int f);

void dfs2(int x, int t);

void mod(int x, int y, int v);

int query(int x, int y);

}  // namespace HLD

int col[MAX_N];

template <typename T>
T read();

int main() {
    // std::ios::sync_with_stdio(false);

    int n = read<int>(), m = read<int>();
    for (int i = 1; i <= n; i++) {
        col[i] = read<int>();
    }

    for (int i = 1; i < n; i++) {
        int x = read<int>(), y = read<int>();
        Star::create(x, y);
        Star::create(y, x);
    }
    HLD::dfs1(1, 0);
    HLD::dfs2(1, 1);
    Tree::build(1, 1, n);

    for (int i = 1; i <= m; i++) {
        char op;
        std::cin >> op;

        if (op == 'C') {
            int x = read<int>(), y = read<int>(), z = read<int>();
            HLD::mod(x, y, z);
        } else {
            int x = read<int>(), y = read<int>();
            std::cout << HLD::query(x, y) << '\n';
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

void update(int x) {
    tree[x].c = tree[x * 2].c + tree[x * 2 + 1].c;

    if (tree[x * 2].rc == tree[x * 2 + 1].lc) {
        tree[x].c--;
    }
    tree[x].lc = tree[x * 2].lc;
    tree[x].rc = tree[x * 2 + 1].rc;
}

void pushdown(int x) {
    if (tree[x].t) {
        if (x * 2) {
            tree[x * 2].lc = tree[x * 2].rc = tree[x * 2].t = tree[x].t;
            tree[x * 2].c = 1;
        }
        if (x * 2 + 1) {
            tree[x * 2 + 1].lc = tree[x * 2 + 1].rc = tree[x * 2 + 1].t =
                tree[x].t;
            tree[x * 2 + 1].c = 1;
        }
        tree[x].t = 0;
    }
}

void build(int x, int l, int r) {
    tree[x].l = l;
    tree[x].r = r;

    if (l == r) {
        tree[x].lc = tree[x].rc = col[HLD::w[l]];
        tree[x].c = 1;
    } else {
        int mid = (l + r) / 2;
        build(x * 2, l, mid);
        build(x * 2 + 1, mid + 1, r);
        update(x);
    }
}

void mod(int x, int l, int r, int v) {
    if (l <= tree[x].l and tree[x].r <= r) {
        tree[x].lc = tree[x].rc = v;
        tree[x].c = 1;
        tree[x].t = v;
    } else {
        pushdown(x);
        int mid = (tree[x].l + tree[x].r) / 2;
        if (l <= mid) {
            mod(x * 2, l, r, v);
        }
        if (mid < r) {
            mod(x * 2 + 1, l, r, v);
        }
        update(x);
    }
}

int query(int x, int l, int r) {
    if (l <= tree[x].l and tree[x].r <= r) {
        if (l == tree[x].l) {
            lc = tree[x].lc;
        }
        if (r == tree[x].r) {
            rc = tree[x].rc;
        }
        return tree[x].c;
    } else {
        pushdown(x);
        int mid = (tree[x].l + tree[x].r) / 2;
        if (r <= mid) {
            return query(x * 2, l, r);
        }
        if (mid < l) {
            return query(x * 2 + 1, l, r);
        }
        int res = query(x * 2, l, r) + query(x * 2 + 1, l, r);
        if (tree[x * 2].rc == tree[x * 2 + 1].lc) {
            res--;
        }
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
    w[idx] = x;
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

void mod(int x, int y, int v) {
    while (top[x] != top[y]) {
        if (dep[top[x]] < dep[top[y]]) {
            std::swap(x, y);
        }
        Tree::mod(1, dfn[top[x]], dfn[x], v);
        x = fa[top[x]];
    }
    if (dfn[x] > dfn[y]) {
        std::swap(x, y);
    }
    Tree::mod(1, dfn[x], dfn[y], v);
}

int query(int x, int y) {
    p1 = p2 = 0;
    int res = 0;

    while (top[x] != top[y]) {
        if (dep[top[x]] < dep[top[y]]) {
            std::swap(x, y);
            std::swap(p1, p2);
        }
        res += Tree::query(1, dfn[top[x]], dfn[x]);
        if (Tree::rc == p1) {
            res--;
        }
        p1 = Tree::lc;
        x = fa[top[x]];
    }
    if (dfn[x] > dfn[y]) {
        std::swap(x, y);
        std::swap(p1, p2);
    }
    res += Tree::query(1, dfn[x], dfn[y]);
    if (Tree::lc == p1) {
        res--;
    }
    if (Tree::rc == p2) {
        res--;
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