#include <climits>
#include <cstdio>
#include <iomanip>
#include <iostream>
#include <memory>

using ll = long long;

constexpr int MAX_N = 100050;
constexpr int MAX_M = 8000050;
constexpr int N = INT_MAX;

class SegTree {
    struct {
        int l;
        int r;
        int lc;
        int rc;
        ll s;
        ll t;
    } tree[MAX_M];

    int cnt;

    void seg_merge(const int x);

    void pushdown(const int x);

   public:
    SegTree() = default;
    ~SegTree() = default;

    int root;

    void mod(int& x, int l, int r, const int ml, const int mr, const int mv);

    ll query(int x, const int ql, const int qr);
};

template <typename T>
T read();

template <typename T>
void read(T& t);

template <typename T, typename... Args>
void read(T& t, Args&... rest);

int main() {
    std::ios::sync_with_stdio(false);
    std::cout << std::fixed << std::setprecision(4);

    int n, m;
    read(n, m);
    auto segTree = std::make_unique<SegTree>();
    for (int i = 1; i <= n; i++) {
        int a, w;
        read(a, w);
        segTree->mod(segTree->root, 1, N, a, N, w);
    }
    while (m--) {
        int op, x, y;
        read(op, x, y);
        if (op == 1) {
            std::cout << (1.0 * segTree->query(segTree->root, x, y) /
                          (y - x + 1))
                      << '\n';
        } else if (op == 2) {
            segTree->mod(segTree->root, 1, N, x, N, y);
        }
    }

    return 0;
}

#define lc (tree[x].lc)
#define rc (tree[x].rc)

void SegTree::seg_merge(const int x) { tree[x].s = tree[lc].s + tree[rc].s; }

void SegTree::pushdown(const int x) {
    if (!tree[x].t) {
        return;
    }
    const auto mid = (tree[x].l + tree[x].r) >> 1;
    if (!lc) {
        lc = ++cnt;
        tree[lc].l = tree[x].l;
        tree[lc].r = mid;
    }
    if (!rc) {
        rc = ++cnt;
        tree[rc].l = mid + 1;
        tree[rc].r = tree[x].r;
    }

    tree[lc].s += tree[x].t * (tree[lc].r - tree[lc].l + 1);
    tree[lc].t += tree[x].t;
    tree[rc].s += tree[x].t * (tree[rc].r - tree[rc].l + 1);
    tree[rc].t += tree[x].t;
    tree[x].t = 0;
}

void SegTree::mod(int& x, int l, int r, const int ml, const int mr,
                  const int mv) {
    if (!x) {
        x = ++cnt;
        tree[x].l = l;
        tree[x].r = r;
    }
    if (ml <= l and r <= mr) {
        tree[x].s += 1ll * mv * (r - l + 1);
        tree[x].t += mv;
        return;
    }
    pushdown(x);
    const auto mid = (l + r) >> 1;
    if (ml <= mid) {
        mod(lc, l, mid, ml, mr, mv);
    }
    if (mid < mr) {
        mod(rc, mid + 1, r, ml, mr, mv);
    }
    seg_merge(x);
}

ll SegTree::query(int x, const int ql, const int qr) {
    if (!x) {
        return 0;
    }
    if (ql <= tree[x].l and tree[x].r <= qr) {
        return tree[x].s;
    }
    pushdown(x);
    const auto mid = (tree[x].l + tree[x].r) >> 1;
    ll res{};
    if (ql <= mid) {
        res += query(lc, ql, qr);
    }
    if (mid < qr) {
        res += query(rc, ql, qr);
    }
    return res;
}

#undef lc
#undef rc

template <typename T>
T read() {
    T x = 0, f = 1;
    char ch = getchar_unlocked();
    while (!isdigit(ch)) {
        if (ch == '-') f = -1;
        ch = getchar_unlocked();
    }
    while (isdigit(ch)) {
        x = x * 10 + ch - 48;
        ch = getchar_unlocked();
    }
    return x * f;
}

template <typename T>
void read(T& t) {
    t = read<T>();
}

template <typename T, typename... Args>
void read(T& t, Args&... rest) {
    t = read<T>();
    read(rest...);
}