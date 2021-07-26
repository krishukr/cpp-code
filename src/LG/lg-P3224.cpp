#include <cstdio>
#include <iostream>

const int MAX_N = 500050;

namespace DSU {

int fa[MAX_N];

int find(int x);

}  // namespace DSU

namespace Tree {

struct Node {
    int ch[2];  // child
    int v;      // value
    int f;      // parent node
    int s;      // size
} tree[MAX_N];

int root[MAX_N];
int tot;

void update(int x);

void rotate(int x);

void splay(int x, int k);

void mod(int x, int v);

void dfs(int x, int y);

void merge(int x, int y);

int query(int x, int y);

}  // namespace Tree

int n, m;

int num[MAX_N];

template <typename T>
T read();

int main() {
    // std::ios::sync_with_stdio(false);
    // freopen("lg-P3224.in", "r", stdin);
    // freopen("lg-P3224.out", "w", stdout);

    n = read<int>(), m = read<int>();
    for (int i = 1; i <= n; i++) {
        Tree::root[i] = i + n;
        DSU::fa[i] = i;
    }  // initial
    Tree::tot = n + n;

    for (int i = 1; i <= n; i++) {
        using Tree::tree;

        int x = read<int>();
        num[x] = i;

        tree[i + n].s = 1;
        tree[i + n].v = x;
        tree[i + n].f = i;
    }

    for (int i = 1; i <= m; i++) {
        int x = read<int>(), y = read<int>();
        Tree::merge(x, y);
    }

    int q = read<int>();
    for (int kkk = 1; kkk <= q; kkk++) {
        char op;
        std::cin >> op;
        int a = read<int>(), b = read<int>();
        if (op == 'Q') {
            int ans = Tree::query(DSU::find(a), b);
            std::cout << (ans == -1 ? -1 : num[ans]) << '\n';
        }
        if (op == 'B') {
            Tree::merge(a, b);
        }
    }

    return 0;
}

namespace DSU {

int find(int x) {
    if (x == fa[x]) {
        return x;
    } else {
        return fa[x] = find(fa[x]);
    }
}

}  // namespace DSU

namespace Tree {

void update(int x) {
    tree[x].s = tree[tree[x].ch[0]].s + tree[tree[x].ch[1]].s + 1;
}

void rotate(int x) {
    int fa = tree[x].f;
    int gf = tree[fa].f;
    int dir = (tree[fa].ch[1] == x);
    tree[gf].ch[tree[gf].ch[1] == fa] = x;
    tree[x].f = gf;

    tree[fa].ch[dir] = tree[x].ch[dir ^ 1];
    tree[tree[x].ch[dir ^ 1]].f = fa;

    tree[x].ch[dir ^ 1] = fa;
    tree[fa].f = x;

    update(fa);
    update(x);
}

void splay(int x, int k) {
    while (tree[x].f != k) {
        int fa = tree[x].f;
        int gf = tree[fa].f;

        if (gf != k) {
            (tree[gf].ch[0] == fa) xor (tree[fa].ch[0] == x) ? rotate(x)
                                                             : rotate(fa);
        }
        rotate(x);
    }

    if (k <= n) {
        root[k] = x;
    }
}

void mod(int x, int v) {
    int u = root[v];
    int f = v;

    while (u and tree[u].v != x) {
        f = u;
        u = tree[u].ch[tree[u].v < x];
    }
    u = ++tot;

    tree[u].s = 1;
    tree[u].f = f;

    if (f > n) {
        tree[f].ch[tree[f].v < x] = u;
    }
    tree[u].v = x;
    tree[u].ch[0] = tree[u].ch[1] = 0;
    splay(u, v);
}

void dfs(int x, int y) {
    if (tree[x].ch[0]) {
        dfs(tree[x].ch[0], y);
    }
    if (tree[x].ch[1]) {
        dfs(tree[x].ch[1], y);
    }
    mod(tree[x].v, y);
}

void merge(int x, int y) {
    int fx = DSU::find(x);
    int fy = DSU::find(y);

    if (fx == fy) {
        return;
    } else {
        if (tree[root[fx]].s > tree[root[fy]].s) {
            std::swap(fx, fy);
        }
        DSU::fa[fx] = fy;
        dfs(root[fx], fy);
    }
}

int query(int x, int y) {
    int u = root[x];
    if (tree[u].s < y) {
        return -1;
    }

    while (true) {
        if (tree[tree[u].ch[0]].s + 1 < y) {
            y -= tree[tree[u].ch[0]].s + 1;
            u = tree[u].ch[1];
        } else {
            if (tree[tree[u].ch[0]].s >= y) {
                u = tree[u].ch[0];
            } else {
                return tree[u].v;
            }
        }
    }
}

}  // namespace Tree

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