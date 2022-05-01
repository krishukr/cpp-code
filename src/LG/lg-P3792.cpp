#include <climits>
#include <cstdio>
#include <iostream>
#include <memory>

using ll = __int128_t;

constexpr static int MAX_N = 500050;

class SegTree {
   private:
   protected:
    std::unique_ptr<int[]> A;

    struct Node {
        int mx;
        int mn;
        ll sm;
    } tree[MAX_N << 2];

    void seg_merge(const int& x);

    void build(int x, int l, int r);

   public:
    SegTree() = default;
    SegTree(const int& n, std::unique_ptr<int[]> A) {
        this->A = std::move(A);
        build(1, 1, n);
    }
    ~SegTree() = default;

    void mod(int x, int l, int r, const int& mk, const int& mv);

    int query_mx(int x, int l, int r, const int& ql, const int& qr);

    int query_mn(int x, int l, int r, const int& ql, const int& qr);

    ll query_sm(int x, int l, int r, const int& ql, const int& qr);
};

template <typename T>
T read();

template <typename T>
void read(T& t);

template <typename T, typename... Args>
void read(T& t, Args&... rest);

int main() {
    std::ios::sync_with_stdio(false);

    int n, m;
    read(n, m);
    auto A = std::make_unique<int[]>(n + 50);
    for (int i = 1; i <= n; i++) {
        read(A[i]);
    }

    auto segTree = std::make_unique<SegTree>(n, std::move(A));
    while (m--) {
        int op, x, y;
        read(op, x, y);
        if (op == 1) {
            segTree->mod(1, 1, n, x, y);
        } else if (op == 2) {
            const int b = segTree->query_mn(1, 1, n, x, y),
                      d = segTree->query_mx(1, 1, n, x, y);
            if (y - x == d - b) {
                ll s = ((ll)d * (d + 1) * (2 * d + 1) / 6) -
                       ((ll)(b - 1) * (b) * (2 * (b - 1) + 1) / 6);
                if (s == segTree->query_sm(1, 1, n, x, y)) {
                    std::cout << "damushen\n";
                    continue;
                }
            }
            std::cout << "yuanxing\n";
        }
    }

    return 0;
}

#define lc x * 2
#define rc x * 2 + 1

void SegTree::seg_merge(const int& x) {
    tree[x].mx = std::max(tree[lc].mx, tree[rc].mx);
    tree[x].mn = std::min(tree[lc].mn, tree[rc].mn);
    tree[x].sm = tree[lc].sm + tree[rc].sm;
}

void SegTree::build(int x, int l, int r) {
    if (l == r) {
        tree[x] = {A[l], A[l], (ll)A[l] * A[l]};
        return;
    }
    const int mid = (l + r) >> 1;
    build(lc, l, mid);
    build(rc, mid + 1, r);
    seg_merge(x);
}

void SegTree::mod(int x, int l, int r, const int& mk, const int& mv) {
    if (l == r) {
        tree[x] = {mv, mv, (ll)mv * mv};
        return;
    }
    const int mid = (l + r) >> 1;
    if (mk <= mid) {
        mod(lc, l, mid, mk, mv);
    } else {
        mod(rc, mid + 1, r, mk, mv);
    }
    seg_merge(x);
}

int SegTree::query_mx(int x, int l, int r, const int& ql, const int& qr) {
    if (ql <= l and r <= qr) {
        return tree[x].mx;
    }
    const int mid = (l + r) >> 1;
    int res = INT_MIN;
    if (ql <= mid) {
        res = std::max(res, query_mx(lc, l, mid, ql, qr));
    }
    if (mid < qr) {
        res = std::max(res, query_mx(rc, mid + 1, r, ql, qr));
    }
    return res;
}

int SegTree::query_mn(int x, int l, int r, const int& ql, const int& qr) {
    if (ql <= l and r <= qr) {
        return tree[x].mn;
    }
    const int mid = (l + r) >> 1;
    int res = INT_MAX;
    if (ql <= mid) {
        res = std::min(res, query_mn(lc, l, mid, ql, qr));
    }
    if (mid < qr) {
        res = std::min(res, query_mn(rc, mid + 1, r, ql, qr));
    }
    return res;
}

ll SegTree::query_sm(int x, int l, int r, const int& ql, const int& qr) {
    if (ql <= l and r <= qr) {
        return tree[x].sm;
    }
    const int mid = (l + r) >> 1;
    ll res = 0;
    if (ql <= mid) {
        res += query_sm(lc, l, mid, ql, qr);
    }
    if (mid < qr) {
        res += query_sm(rc, mid + 1, r, ql, qr);
    }
    return res;
}

#undef lc
#undef rc

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

template <typename T>
void read(T& t) {
    t = read<T>();
}

template <typename T, typename... Args>
void read(T& t, Args&... rest) {
    t = read<T>();
    read(rest...);
}