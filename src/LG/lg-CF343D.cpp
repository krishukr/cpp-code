#include <cstdio>
#include <iostream>

int n;

template <typename T>
T read();

class Star {
   private:
    const static int MAX_N = 500050;

   protected:
    struct Node {
        int v;
        int nxt;
    } node[MAX_N << 1];

    int head[MAX_N << 1];
    int cnt;

   public:
    void create(int u, int v) {
        node[++cnt].v = v;
        node[cnt].nxt = head[u];
        head[u] = cnt;
    }
};

class SegTree {
   private:
    const static int MAX_N = 500050;

   protected:
    struct Node {
        int s;
        int t;
    } tree[MAX_N << 2];

    void update(int x) { tree[x].s = tree[x * 2].s + tree[x * 2 + 1].s; }

    void pushdown(int x, int l, int r) {
        if (tree[x].t != -1) {
            int mid = (l + r) / 2;
            tree[x * 2].t = tree[x * 2 + 1].t = tree[x].t;
            tree[x * 2].s = tree[x].t * (mid - l + 1);
            tree[x * 2 + 1].s = tree[x].t * (r - mid);
            tree[x].t = -1;
        }
    }

    void build(int x, int l, int r) {
        if (l == r) {
            tree[x].s = 0;
            return;
        }
        int mid = (l + r) / 2;
        build(x * 2, l, mid);
        build(x * 2 + 1, mid + 1, r);
        update(x);
    }

   public:
    SegTree() { build(1, 1, n); }

    void mod(int x, int l, int r, int ql, int qr, int w) {
        if (ql <= l and r <= qr) {
            tree[x].s = (r - l + 1) * w;
            tree[x].t = w;
            return;
        }
        pushdown(x, l, r);
        int mid = (l + r) / 2;
        if (ql <= mid) {
            mod(x * 2, l, mid, ql, qr, w);
        }
        if (qr > mid) {
            mod(x * 2 + 1, mid + 1, r, ql, qr, w);
        }
        update(x);
    }

    int query(int x, int l, int r, int k) {
        if (l == r) {
            return tree[x].s;
        }
        pushdown(x, l, r);
        int mid = (l + r) / 2;
        if (k <= mid) {
            return query(x * 2, l, mid, k);
        } else {
            return query(x * 2 + 1, mid + 1, r, k);
        }
    }
};

class HLD : public Star, public SegTree {
   private:
    const static int MAX_N = 500050;

   protected:
    void dfs1(int x, int f) {
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
        for (int i = head[x]; i; i = node[i].nxt) {
            int v = node[i].v;
            if (v == fa[x] or v == son[x]) {
                continue;
            }
            dfs2(v, v);
        }
    }

   public:
    int fa[MAX_N], son[MAX_N], top[MAX_N], dep[MAX_N], dfn[MAX_N], siz[MAX_N];
    int idx;

    HLD() {
        for (int i = 1; i < n; i++) {
            int x = read<int>(), y = read<int>();
            create(x, y);
            create(y, x);
        }

        dep[1] = 1;
        dfs1(1, 0);
        dfs2(1, 1);
    }

    void mod_path(int x) {
        while (x) {
            mod(1, 1, n, dfn[top[x]], dfn[x], 0);
            x = fa[top[x]];
        }
    }
};

class Solution {
   private:
    HLD* hld;

   public:
    void solve() {
        n = read<int>();

        hld = new HLD();

        int m = read<int>();
        for (int i = 1; i <= m; i++) {
            int op = read<int>(), x = read<int>();
            if (op == 1) {
                hld->mod(1, 1, n, hld->dfn[x], hld->dfn[x] + hld->siz[x] - 1,
                         1);
            }
            if (op == 2) {
                hld->mod_path(x);
            }
            if (op == 3) {
                std::cout << hld->query(1, 1, n, hld->dfn[x]) << '\n';
            }
        }

        delete hld;
    }
};

int main() {
    std::ios::sync_with_stdio(false);

    Solution* soulution = new Solution();
    soulution->solve();
    delete soulution;

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
}