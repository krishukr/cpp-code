#include <cstdio>
#include <iostream>
#include <memory>

using ll = long long;

constexpr int MAX_N = 100050;
int MOD;

class SegTree {
    struct {
        ll s;
        ll m;
        ll a;
    } tree[MAX_N << 2];

    void pushdown(const int& x, const int& l, const int& r);

    void seg_merge(const int& x);

    void build(int x, int l, int r);

   public:
    SegTree() = default;
    SegTree(const int n) { build(1, 1, n); }
    ~SegTree() = default;

    void mod_mul(int x, int l, int r, const int& ml, const int& mr,
                 const ll& mv);

    void mod_add(int x, int l, int r, const int& ml, const int& mr,
                 const ll& mv);

    ll query(int x, int l, int r, const int& ql, const int& qr);
};

ll a[MAX_N];

template <typename T>
T read();

template <typename T>
void read(T& t);

template <typename T, typename... Args>
void read(T& t, Args&... rest);

int main() {
    std::ios::sync_with_stdio(false);

    int n, m;
    read(n, MOD);
    for (int i = 1; i <= n; i++) {
        read(a[i]);
    }
    std::unique_ptr<SegTree> segTree(new SegTree(n));

    read(m);
    while (m--) {
        int op, x, y;
        read(op, x, y);
        if (op == 1) {
            ll z{};
            read(z);
            segTree->mod_mul(1, 1, n, x, y, z);
        } else if (op == 2) {
            ll z;
            read(z);
            segTree->mod_add(1, 1, n, x, y, z);
        } else if (op == 3) {
            std::cout << segTree->query(1, 1, n, x, y) << '\n';
        }
    }

    return 0;
}

#define lc (x << 1)
#define rc ((x << 1) | 1)

void SegTree::pushdown(const int& x, const int& l, const int& r) {
    if (tree[x].m != 1 or tree[x].a != 0) {
        const auto mid = (l + r) >> 1;
        tree[lc].s =
            (tree[lc].s * tree[x].m + (ll)(mid - l + 1) * tree[x].a) % MOD;
        tree[lc].m = (tree[lc].m * tree[x].m) % MOD;
        tree[lc].a = (tree[lc].a * tree[x].m + tree[x].a) % MOD;
        tree[rc].s = (tree[rc].s * tree[x].m + (ll)(r - mid) * tree[x].a) % MOD;
        tree[rc].m = (tree[rc].m * tree[x].m) % MOD;
        tree[rc].a = (tree[rc].a * tree[x].m + tree[x].a) % MOD;
        tree[x].m = 1;
        tree[x].a = 0;
    }
}

void SegTree::seg_merge(const int& x) {
    tree[x].s = (tree[lc].s + tree[rc].s) % MOD;
}

void SegTree::build(int x, int l, int r) {
    tree[x].m = 1;
    if (l == r) {
        tree[x] = {a[l], 1, 0};
        return;
    }
    const auto mid = (l + r) >> 1;
    build(lc, l, mid);
    build(rc, mid + 1, r);
    seg_merge(x);
}

void SegTree::mod_mul(int x, int l, int r, const int& ml, const int& mr,
                      const ll& mv) {
    if (ml <= l and r <= mr) {
        tree[x] = {tree[x].s * mv % MOD, tree[x].m * mv % MOD,
                   tree[x].a * mv % MOD};
        return;
    }
    pushdown(x, l, r);
    const auto mid = (l + r) >> 1;
    if (ml <= mid) {
        mod_mul(lc, l, mid, ml, mr, mv);
    }
    if (mid < mr) {
        mod_mul(rc, mid + 1, r, ml, mr, mv);
    }
    seg_merge(x);
}

void SegTree::mod_add(int x, int l, int r, const int& ml, const int& mr,
                      const ll& mv) {
    if (ml <= l and r <= mr) {
        tree[x] = {(tree[x].s + mv * (r - l + 1)) % MOD, tree[x].m,
                   (tree[x].a + mv) % MOD};
        return;
    }
    pushdown(x, l, r);
    const auto mid = (l + r) >> 1;
    if (ml <= mid) {
        mod_add(lc, l, mid, ml, mr, mv);
    }
    if (mid < mr) {
        mod_add(rc, mid + 1, r, ml, mr, mv);
    }
    seg_merge(x);
}

ll SegTree::query(int x, int l, int r, const int& ql, const int& qr) {
    if (ql <= l and r <= qr) {
        return tree[x].s;
    }
    pushdown(x, l, r);
    const auto mid = (l + r) >> 1;
    ll res{};
    if (ql <= mid) {
        res += query(lc, l, mid, ql, qr);
    }
    if (mid < qr) {
        res += query(rc, mid + 1, r, ql, qr);
    }
    return res % MOD;
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