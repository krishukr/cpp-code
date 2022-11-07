#include <climits>
#include <cstdio>
#include <iostream>
#include <memory>

constexpr int MAX_N = 100050;

class SegTree {
    struct {
        int m;
    } tree[MAX_N << 2];

    void seg_merge(const int& x);

    void build(int x, int l, int r);

   public:
    SegTree() = default;
    SegTree(int n) { build(1, 1, n); }
    ~SegTree() = default;

    void mod(int x, int l, int r, const int& mk, const int& mv);

    int query(int x, int l, int r, const int& ql, const int& qr);
};

int a[MAX_N];

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
    for (int i = 1; i <= n; i++) {
        read(a[i]);
    }
    std::unique_ptr<SegTree> segTree(new SegTree(n));

    while (m--) {
        int x, y, z;
        read(x, y, z);
        if (x == 1) {
            std::cout << segTree->query(1, 1, n, y, z) << ' ';
        } else if (x == 2) {
            segTree->mod(1, 1, n, y, z);
        }
    }
    std::cout << '\n';

    return 0;
}

#define lc (x << 1)
#define rc ((x << 1) | 1)

void SegTree::seg_merge(const int& x) {
    tree[x].m = std::min(tree[lc].m, tree[rc].m);
}

void SegTree::build(int x, int l, int r) {
    if (l == r) {
        tree[x] = {a[l]};
        return;
    }
    const auto mid = (l + r) >> 1;
    build(lc, l, mid);
    build(rc, mid + 1, r);
    seg_merge(x);
}

void SegTree::mod(int x, int l, int r, const int& mk, const int& mv) {
    if (l == r) {
        tree[x] = {mv};
        return;
    }
    const auto mid = (l + r) >> 1;
    if (mk <= mid) {
        mod(lc, l, mid, mk, mv);
    } else {
        mod(rc, mid + 1, r, mk, mv);
    }
    seg_merge(x);
}

int SegTree::query(int x, int l, int r, const int& ql, const int& qr) {
    if (ql <= l and r <= qr) {
        return tree[x].m;
    }
    const auto mid = (l + r) >> 1;
    int res{INT_MAX};
    if (ql <= mid) {
        res = std::min(res, query(lc, l, mid, ql, qr));
    }
    if (mid < qr) {
        res = std::min(res, query(rc, mid + 1, r, ql, qr));
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