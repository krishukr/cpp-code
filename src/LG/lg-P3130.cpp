#include <cstdio>
#include <iostream>

#define int long long

class SegTree {
   private:
    const static int MAX_N = 800050;
    int *v;

   protected:
    struct Node {
        int s;
        int m;
        int t;
        int l;
    } tree[MAX_N << 2];

    void update(int x) {
        tree[x].s = tree[x * 2].s + tree[x * 2 + 1].s;
        tree[x].m = std::min(tree[x * 2].m, tree[x * 2 + 1].m);
    }

    void pushdown(int x) {
        if (tree[x].t) {
            tree[x * 2].t += tree[x].t;
            tree[x * 2 + 1].t += tree[x].t;
            tree[x * 2].s += tree[x * 2].l * tree[x].t;
            tree[x * 2 + 1].s += tree[x * 2 + 1].l * tree[x].t;
            tree[x * 2].m += tree[x].t;
            tree[x * 2 + 1].m += tree[x].t;
            tree[x].t = 0;
        }
    }

    void build(int x, int l, int r) {
        tree[x].l = (r - l + 1);
        if (l == r) {
            tree[x].s = v[l];
            tree[x].m = v[l];
            return;
        }

        int mid = (l + r) / 2;
        build(x * 2, l, mid);
        build(x * 2 + 1, mid + 1, r);
        update(x);
    }

   public:
    SegTree() = delete;
    SegTree(int n, int *v) {
        this->v = v;
        build(1, 1, n);
    }
    ~SegTree() = default;

    void mod(int x, int l, int r, int ql, int qr, int w) {
        if (ql <= l and r <= qr) {
            tree[x].s += tree[x].l * w;
            tree[x].t += w;
            tree[x].m += w;
            return;
        }
        pushdown(x);
        int mid = (l + r) / 2;
        if (ql <= mid) {
            mod(x * 2, l, mid, ql, qr, w);
        }
        if (mid < qr) {
            mod(x * 2 + 1, mid + 1, r, ql, qr, w);
        }
        update(x);
    }

    int query(int x, int l, int r, int ql, int qr) {
        if (ql <= l and r <= qr) {
            return tree[x].s;
        }
        pushdown(x);
        int mid = (l + r) / 2, ans = 0;
        if (ql <= mid) {
            ans += query(x * 2, l, mid, ql, qr);
        }
        if (mid < qr) {
            ans += query(x * 2 + 1, mid + 1, r, ql, qr);
        }
        return ans;
    }

    int min(int x, int l, int r, int ql, int qr) {
        if (ql <= l and r <= qr) {
            return tree[x].m;
        }
        pushdown(x);
#ifdef int
        int mid = (l + r) / 2, ans = 0x3f3f3f3f3f3f3f3f;
#else
        int mid = (l + r) / 2, ans = 0x3f3f3f3f;
#endif
        if (ql <= mid) {
            ans = std::min(ans, min(x * 2, l, mid, ql, qr));
        }
        if (mid < qr) {
            ans = std::min(ans, min(x * 2 + 1, mid + 1, r, ql, qr));
        }
        return ans;
    }
};

template <typename T>
T read();

signed main() {
    std::ios::sync_with_stdio(false);

    int n = read<int>(), q = read<int>();
    auto *v = new int[n + 10];

    for (int i = 1; i <= n; i++) {
        v[i] = read<int>();
    }
    auto *segTree = new SegTree(n, v);

    while (q--) {
        char op;
        scanf("%c", &op);

        if (op == 'M') {
            int x = read<int>(), y = read<int>();
            std::cout << segTree->min(1, 1, n, x, y) << '\n';
        }
        if (op == 'P') {
            int x = read<int>(), y = read<int>(), z = read<int>();
            segTree->mod(1, 1, n, x, y, z);
        }
        if (op == 'S') {
            int x = read<int>(), y = read<int>();
            std::cout << segTree->query(1, 1, n, x, y) << '\n';
        }
    }

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