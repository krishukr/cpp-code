#include <bits/stdc++.h>

using ll = long long;

constexpr int MAX_N = 100050;

class SegTree {
   private:
    struct {
        ll a;
        ll t;
    } tree[MAX_N << 2];

    void pushdown(uint x, int l, int r);

    void update(uint x);

    void build(uint x, int l, int r);

   public:
    SegTree(int n);
    ~SegTree() = default;

    void add(uint x, int l, int r, int ml, int mr, int k);

    ll query(uint x, int l, int r, int ql, int qr);
};

ll a[MAX_N];

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(0);

    int n, m;
    std::cin >> n >> m;
    for (int i = 1; i <= n; i++) {
        std::cin >> a[i];
    }
    auto segTree = std::make_unique<SegTree>(n);

    while (m--) {
        int op, x, y, k;
        std::cin >> op >> x >> y;
        if (op == 1) {
            std::cin >> k;
            segTree->add(1, 1, n, x, y, k);
        } else {
            std::cout << segTree->query(1, 1, n, x, y) << '\n';
        }
    }

    std::cout << std::flush;
    return 0;
}

#define lc (x << 1)
#define rc (x << 1 | 1)

SegTree::SegTree(int n) { build(1, 1, n); }

void SegTree::build(uint x, int l, int r) {
    if (l == r) {
        tree[x].a = a[l];
        return;
    } else {
        const int mid = (l + r) >> 1;
        build(lc, l, mid);
        build(rc, mid + 1, r);
        update(x);
    }
}

void SegTree::update(uint x) { tree[x].a = tree[lc].a + tree[rc].a; }

void SegTree::pushdown(uint x, int l, int r) {
    const int mid = (l + r) >> 1;
    tree[lc].t += tree[x].t;
    tree[rc].t += tree[x].t;
    tree[lc].a += tree[x].t * (mid - l + 1);
    tree[rc].a += tree[x].t * (r - mid);
    tree[x].t = 0;
}

void SegTree::add(uint x, int l, int r, int ml, int mr, int k) {
    if (ml <= l and r <= mr) {
        tree[x].a += k * (r - l + 1);
        tree[x].t += k;
        return;
    } else {
        if (tree[x].t) {
            pushdown(x, l, r);
        }
        const int mid = (l + r) >> 1;
        if (ml <= mid) {
            add(lc, l, mid, ml, mr, k);
        }
        if (mid < mr) {
            add(rc, mid + 1, r, ml, mr, k);
        }
        update(x);
    }
}

ll SegTree::query(uint x, int l, int r, int ql, int qr) {
    if (ql <= l and r <= qr) {
        return tree[x].a;
    } else {
        const int mid = (l + r) >> 1;
        if (tree[x].t) {
            pushdown(x, l, r);
        }
        ll res{};
        if (ql <= mid) {
            res += query(lc, l, mid, ql, qr);
        }
        if (mid < qr) {
            res += query(rc, mid + 1, r, ql, qr);
        }
        return res;
    }
}

#undef lc
#undef rc
