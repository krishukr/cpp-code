#include <cstdio>
#include <iostream>

int n, m;

template <typename T>
T read();

class SegTree {
   private:
    const static int MAX_N = 400050;

   protected:
    struct Node {
        int w;
        int t;
    } tree[MAX_N];

    void update(int x) { tree[x].w = tree[x * 2].w + tree[x * 2 + 1].w; }

    void pushdown(int x, int l, int r) {
        if (tree[x].t) {
            tree[x * 2].t += tree[x].t;
            tree[x * 2 + 1].t += tree[x].t;

            int mid = (l + r) / 2;
            tree[x * 2].w += tree[x].t * (mid - l + 1);
            tree[x * 2 + 1].w += tree[x].t * (r - mid);
            tree[x].t = 0;
        }
    }

   public:
    void mod(int x, int l, int r, int ql, int qr, int w = 1) {
        if (ql <= l and r <= qr) {
            tree[x].w += (r - l + 1) * w;
            tree[x].t += w;
            return;
        }
        int mid = (l + r) / 2;
        pushdown(x, l, r);
        if (ql <= mid) {
            mod(x * 2, l, mid, ql, qr);
        }
        if (mid < qr) {
            mod(x * 2 + 1, mid + 1, r, ql, qr);
        }
        update(x);
    }

    int query(int x, int l, int r, int ql, int qr) {
        if (ql <= l and r <= qr) {
            return tree[x].w;
        }
        int mid = (l + r) / 2, res = 0;
        pushdown(x, l, r);
        if (ql <= mid) {
            res += query(x * 2, l, mid, ql, qr);
        }
        if (mid < qr) {
            res += query(x * 2 + 1, mid + 1, r, ql, qr);
        }
        return res;
    }
};

class Star {
   private:
    const static int MAX_N = 200050;

   public:
    struct Node {
        int v;
        int nxt;
    } node[MAX_N];

    int head[MAX_N];
    int cnt;

    void create(int u, int v) {
        node[++cnt].v = v;
        node[cnt].nxt = head[u];
        head[u] = cnt;
    }
};

class HLD {
   private:
    const static int MAX_N = 100050;
    Star* star;
    SegTree* segtree;

   protected:
    int fa[MAX_N], son[MAX_N], top[MAX_N], dep[MAX_N], dfn[MAX_N], siz[MAX_N];
    int idx;

    void dfs1(int x, int f) {
        dep[x] = dep[f] + 1;
        fa[x] = f;
        siz[x] = 1;

        for (int i = star->head[x]; i; i = star->node[i].nxt) {
            int v = star->node[i].v;
            if (v == f) {
                continue;
            }
            dfs1(v, x);
            siz[x] += siz[v];

            if (siz[son[x]] <= siz[v]) {
                son[x] = v;
            }
        }
    }

    void dfs2(int x, int t) {
        dfn[x] = ++idx;
        top[x] = t;

        if (son[x]) {
            dfs2(son[x], t);
        }
        for (int i = star->head[x]; i; i = star->node[i].nxt) {
            int v = star->node[i].v;
            if (v == fa[x] or v == son[x]) {
                continue;
            }
            dfs2(v, v);
        }
    }

   public:
    HLD(Star* s, SegTree* t) {
        star = s;
        segtree = t;

        dep[1] = 1;
    }

    void dfs() {
        dfs1(1, 0);
        dfs2(1, 1);
    }

    void mod_path(int x, int y) {
        while (top[x] != top[y]) {
            if (dep[top[x]] < dep[top[y]]) {
                std::swap(x, y);
            }
            segtree->mod(1, 1, n, dfn[top[x]], dfn[x]);
            x = fa[top[x]];
        }
        if (dep[x] > dep[y]) {
            std::swap(x, y);
        }
        segtree->mod(1, 1, n, dfn[x] + 1, dfn[y]);
    }

    int query_path(int x, int y) {
        int res = 0;
        while (top[x] != top[y]) {
            if (dep[top[x]] < dep[top[y]]) {
                std::swap(x, y);
            }
            res += segtree->query(1, 1, n, dfn[top[x]], dfn[x]);
            x = fa[top[x]];
        }
        if (dep[x] > dep[y]) {
            std::swap(x, y);
        }
        if (x != y) {
            res += segtree->query(1, 1, n, dfn[x] + 1, dfn[y]);
        }
        return res;
    }
};

class Solution {
   private:
    Star* star = new Star();
    SegTree* segtree = new SegTree();
    HLD* hld = new HLD(star, segtree);

   public:
    void solve() {
        n = read<int>(), m = read<int>();
        for (int i = 1; i < n; i++) {
            int x = read<int>(), y = read<int>();
            star->create(x, y);
            star->create(y, x);
        }

        hld->dfs();

        while (m--) {
            char op;
            std::cin >> op;
            int x = read<int>(), y = read<int>();
            if (op == 'P') {
                hld->mod_path(x, y);
            }
            if (op == 'Q') {
                std::cout << hld->query_path(x, y) << '\n';
            }
        }
    }
};

int main() {
    // std::ios::sync_with_stdio(false);

    Solution* solution = new Solution();
    solution->solve();
    delete solution;

    return 0;
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
};