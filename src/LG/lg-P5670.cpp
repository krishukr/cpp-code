#include <bitset>
#include <cstdio>
#include <iostream>

constexpr int MAX_N = 100050;
constexpr size_t MAX_M = 1 << 10;

using bit = std::bitset<MAX_M>;

class SegTree {
   protected:
    struct Node {
        bit b;
        int t;
    } tree[MAX_N];

    int a[MAX_N];

    void pushdown(const int& x);

    void seg_merge(const int& x);

   public:
    SegTree() = default;
    SegTree(const int& n) { build(1, 1, n); }
    ~SegTree() = default;

    void build(int x, int l, int r);

    void mod(int x, int l, int r, const int& ml, const int& mr, const int& mv);

    void query(int x, int l, int r, const int& ql, const int& qr, bit& res);
};

template <typename T = int>
T read();

int main() {
    std::ios::sync_with_stdio(false);

    int n = read(), m = read(), q = read();
    auto* segTree = new SegTree(n);

    while (q--) {
        int op = read(), l = read(), r = read();
        if (op == 1) {
            int x = read();
            segTree->mod(1, 1, n, l, r, x);
        } else if (op == 2) {
            bit b;
            segTree->query(1, 1, n, l, r, b);
            int ans = 0;
            for (int i = 0; i < MAX_M; i++) {
                ans ^= b[i] * i;
            }
            ans &= (1 << m) - 1;
            std::cout << ans << '\n';
        }
    }

    return 0;
}

#define lc x * 2
#define rc x * 2 + 1

void SegTree::pushdown(const int& x) {
    if (tree[x].t) {
        tree[lc].b =
            (tree[lc].b << tree[x].t) | (tree[lc].b >> (MAX_M - tree[x].t));
        tree[lc].t += tree[x].t;
        tree[lc].t &= MAX_M - 1;
        tree[rc].b =
            (tree[rc].b << tree[x].t) | (tree[rc].b >> (MAX_M - tree[x].t));
        tree[rc].t += tree[x].t;
        tree[rc].t &= MAX_M - 1;
        tree[x].t = 0;
    }
}

void SegTree::seg_merge(const int& x) { tree[x].b = tree[lc].b ^ tree[rc].b; }

#define len r - l + 1

void SegTree::build(int x, int l, int r) {
    if (len <= 64) {
        for (int i = l; i <= r; i++) {
            a[i] = read();
            tree[x].b.flip(a[i]);
        }
        return;
    }
    int mid = (l + r) >> 1;
    build(lc, l, mid);
    build(rc, mid + 1, r);
    seg_merge(x);
}

void SegTree::mod(int x, int l, int r, const int& ml, const int& mr,
                  const int& mv) {
    if (len <= 64) {
        for (int i = std::max(l, ml); i <= std::min(r, mr); i++) {
            tree[x].b.flip((a[i] + tree[x].t) & (MAX_M - 1));
            a[i] += mv;
            a[i] &= MAX_M - 1;
            tree[x].b.flip((a[i] + tree[x].t) & (MAX_M - 1));
        }
        return;
    }
    if (ml <= l and r <= mr) {
        tree[x].b = (tree[x].b << mv) | (tree[x].b >> (MAX_M - mv));
        tree[x].t += mv;
        tree[x].t &= MAX_M - 1;
        return;
    }
    pushdown(x);
    int mid = (l + r) >> 1;
    if (ml <= mid) {
        mod(lc, l, mid, ml, mr, mv);
    }
    if (mid < mr) {
        mod(rc, mid + 1, r, ml, mr, mv);
    }
    seg_merge(x);
}

void SegTree::query(int x, int l, int r, const int& ql, const int& qr,
                    bit& res) {
    if (len <= 64) {
        for (int i = std::max(l, ql); i <= std::min(r, qr); i++) {
            res.flip((a[i] + tree[x].t) & (MAX_M - 1));
        }
        return;
    }
    if (ql <= l and r <= qr) {
        res ^= tree[x].b;
        return;
    }
    pushdown(x);
    int mid = (l + r) >> 1;
    if (ql <= mid) {
        query(lc, l, mid, ql, qr, res);
    }
    if (mid < qr) {
        query(rc, mid + 1, r, ql, qr, res);
    }
}

#undef len

#undef lc
#undef rc

template <typename T = int>
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