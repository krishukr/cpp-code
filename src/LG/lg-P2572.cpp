#include <cstdio>
#include <iostream>

int n, m;

template <typename T>
T read();

class SegTree {
   private:
    const static int MAX_N = 400050;
    int *w;

   protected:
    struct Node {
        int l;
        int r;
        int s;
        int t;
        int v;
        int m[2], lm[2], rm[2];
    } tree[MAX_N];

    void update(int x) {
        tree[x].s = tree[x * 2].s + tree[x * 2 + 1].s;

        for (int i = 0; i <= 1; i++) {
            tree[x].lm[i] = tree[x * 2].lm[i];
            if (i == 0 and tree[x * 2].s == 0) {
                tree[x].lm[i] += tree[x * 2 + 1].lm[i];
            }
            if (i == 1 and tree[x * 2].s == tree[x * 2].r - tree[x * 2].l + 1) {
                tree[x].lm[i] += tree[x * 2 + 1].lm[i];
            }

            tree[x].rm[i] = tree[x * 2 + 1].rm[i];
            if (i == 0 and tree[x * 2 + 1].s == 0) {
                tree[x].rm[i] += tree[x * 2].rm[i];
            }
            if (i == 1 and tree[x * 2 + 1].s ==
                               tree[x * 2 + 1].r - tree[x * 2 + 1].l + 1) {
                tree[x].rm[i] += tree[x * 2].rm[i];
            }

            tree[x].m[i] = tree[x * 2].rm[i] + tree[x * 2 + 1].lm[i];
            tree[x].m[i] = std::max(tree[x].m[i], tree[x * 2].m[i]);
            tree[x].m[i] = std::max(tree[x].m[i], tree[x * 2 + 1].m[i]);
        }
    }

    void build(int x, int l, int r) {
        tree[x].l = l;
        tree[x].r = r;
        tree[x].t = -1;
        if (l == r) {
            tree[x].s = w[l];
            tree[x].m[1] = tree[x].lm[1] = tree[x].rm[1] = w[l];
            tree[x].m[0] = tree[x].lm[0] = tree[x].rm[0] = !w[l];
            return;
        }

        int mid = (l + r) / 2;
        build(x * 2, l, mid);
        build(x * 2 + 1, mid + 1, r);
        update(x);
    }

    void pushdown(int x) {
        if (tree[x].t != -1) {
            tree[x].v = 0;

            tree[x * 2].s = (tree[x * 2].r - tree[x * 2].l + 1) * tree[x].t;
            tree[x * 2 + 1].s =
                (tree[x * 2 + 1].r - tree[x * 2 + 1].l + 1) * tree[x].t;

            tree[x * 2].t = tree[x * 2 + 1].t = tree[x].t;
            tree[x * 2].v = tree[x * 2 + 1].v = tree[x].v;

            tree[x * 2].m[tree[x].t] = tree[x * 2].lm[tree[x].t] =
                tree[x * 2].rm[tree[x].t] = tree[x * 2].r - tree[x * 2].l + 1;
            tree[x * 2].m[tree[x].t ^ 1] = tree[x * 2].lm[tree[x].t ^ 1] =
                tree[x * 2].rm[tree[x].t ^ 1] = 0;

            tree[x * 2 + 1].m[tree[x].t] = tree[x * 2 + 1].lm[tree[x].t] =
                tree[x * 2 + 1].rm[tree[x].t] =
                    tree[x * 2 + 1].r - tree[x * 2 + 1].l + 1;
            tree[x * 2 + 1].m[tree[x].t ^ 1] =
                tree[x * 2 + 1].lm[tree[x].t ^ 1] =
                    tree[x * 2 + 1].rm[tree[x].t ^ 1] = 0;

            tree[x].t = -1;
        }
        if (tree[x].v) {
            tree[x * 2].s = (tree[x * 2].r - tree[x * 2].l + 1) - tree[x * 2].s;
            tree[x * 2 + 1].s =
                (tree[x * 2 + 1].r - tree[x * 2 + 1].l + 1) - tree[x * 2 + 1].s;

            if (tree[x * 2].t != -1) {
                tree[x * 2].t ^= 1;
            } else {
                tree[x * 2].v ^= 1;
            }
            if (tree[x * 2 + 1].t != -1) {
                tree[x * 2 + 1].t ^= 1;
            } else {
                tree[x * 2 + 1].v ^= 1;
            }

            std::swap(tree[x * 2].m[0], tree[x * 2].m[1]);
            std::swap(tree[x * 2].lm[0], tree[x * 2].lm[1]);
            std::swap(tree[x * 2].rm[0], tree[x * 2].rm[1]);
            std::swap(tree[x * 2 + 1].m[0], tree[x * 2 + 1].m[1]);
            std::swap(tree[x * 2 + 1].lm[0], tree[x * 2 + 1].lm[1]);
            std::swap(tree[x * 2 + 1].rm[0], tree[x * 2 + 1].rm[1]);

            tree[x].v = 0;
        }
    }

   public:
    SegTree(int *i) {
        w = i;
        build(1, 1, n);
    }

    void mod(int x, int ql, int qr, int v) {
        pushdown(x);  // 下方使用了sum等，需要先下传标记
        if (ql <= tree[x].l and tree[x].r <= qr) {
            if (v == 2) {
                tree[x].s = (tree[x].r - tree[x].l + 1) - tree[x].s;
                tree[x].v ^= 1;
                std::swap(tree[x].m[0], tree[x].m[1]);
                std::swap(tree[x].lm[0], tree[x].lm[1]);
                std::swap(tree[x].rm[0], tree[x].rm[1]);
            } else {
                tree[x].s = (tree[x].r - tree[x].l + 1) * v;
                tree[x].t = v;
                tree[x].m[v] = tree[x].lm[v] = tree[x].rm[v] =
                    tree[x].r - tree[x].l + 1;
                tree[x].m[v ^ 1] = tree[x].lm[v ^ 1] = tree[x].rm[v ^ 1] = 0;
            }
            return;
        }

        int mid = (tree[x].l + tree[x].r) / 2;
        if (ql <= mid) {
            mod(x * 2, ql, qr, v);
        }
        if (mid < qr) {
            mod(x * 2 + 1, ql, qr, v);
        }
        update(x);
    }

    int query(int x, int ql, int qr) {
        if (ql <= tree[x].l and tree[x].r <= qr) {
            return tree[x].s;
        }
        int mid = (tree[x].l + tree[x].r) / 2, res = 0;
        pushdown(x);
        if (ql <= mid) {
            res += query(x * 2, ql, qr);
        }
        if (mid < qr) {
            res += query(x * 2 + 1, ql, qr);
        }
        return res;
    }

    Node max(int x, int ql, int qr) {
        if (ql <= tree[x].l and tree[x].r <= qr) {
            return tree[x];
        }
        int mid = (tree[x].l + tree[x].r) / 2;
        Node res{}, l{}, r{};
        pushdown(x);
        if (ql <= mid) {
            l = max(x * 2, ql, qr);
        }
        if (mid < qr) {
            r = max(x * 2 + 1, ql, qr);
        }

        res.s = l.s + r.s;
        for (int i = 0; i <= 1; i++) {
            res.lm[i] = l.lm[i];
            if (i == 0 and l.s == 0) {
                res.lm[i] += r.lm[i];
            }
            if (i == 1 and l.s == l.r - l.l + 1) {
                res.lm[i] += r.lm[i];
            }

            res.rm[i] = r.rm[i];
            if (i == 0 and r.s == 0) {
                res.rm[i] += l.rm[i];
            }
            if (i == 1 and r.s == r.r - r.l + 1) {
                res.rm[i] += l.rm[i];
            }

            res.m[i] = l.rm[i] + r.lm[i];
            res.m[i] = std::max(res.m[i], l.m[i]);
            res.m[i] = std::max(res.m[i], r.m[i]);
        }
        return res;
    }
};

class Solution {
   private:
    const static int MAX_N = 100050;

    SegTree *segtree;

   protected:
    int w[MAX_N];

   public:
    void solve() {
        n = read<int>(), m = read<int>();
        for (int i = 1; i <= n; i++) {
            w[i] = read<int>();
        }

        segtree = new SegTree(w);

        while (m--) {
            int op = read<int>(), x = read<int>(), y = read<int>();
            x++, y++;
            if (op == 0) {
                segtree->mod(1, x, y, 0);
            }
            if (op == 1) {
                segtree->mod(1, x, y, 1);
            }
            if (op == 2) {
                segtree->mod(1, x, y, 2);
            }
            if (op == 3) {
                std::cout << segtree->query(1, x, y) << '\n';
            }
            if (op == 4) {
                std::cout << segtree->max(1, x, y).m[1] << '\n';
            }
        }
    }
};

int main() {
    std::ios::sync_with_stdio(false);

    Solution *solution = new Solution();
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
}