#include <algorithm>
#include <cstdio>
#include <iostream>
#include <memory>

constexpr int MAX_N = 500050;

class SegTree {
   public:
    struct Node {
        int a;
        int b;
        int l;
        int r;
        int m;
    } tree[MAX_N << 2];

   protected:
    constexpr static int INF = -0x3f3f3f3f;

    int A[MAX_N], B[MAX_N];

    Node seg_merge(const Node& x, const Node& y);

    void build(int x, int l, int r);

   public:
    SegTree() = default;
    SegTree(const int n);
    ~SegTree() = default;

    void mod(int x, int l, int r, const int& mk, const int& mv, const int& mo);

    Node query(int x, int l, int r, const int& ql, const int& qr);
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
    auto segTree = std::make_unique<SegTree>(n);
    while (m--) {
        int op, x, y;
        read(op, x, y);
        if (op == 3) {
            std::cout << segTree->query(1, 1, n, x, y).m << '\n';
        } else {
            segTree->mod(1, 1, n, x, y, op);
        }
    }

    return 0;
}

#define lc (x << 1)
#define rc ((x << 1) + 1)

SegTree::Node SegTree::seg_merge(const SegTree::Node& x,
                                 const SegTree::Node& y) {
    return {std::max(x.a, y.a), std::min(x.b, y.b),
            std::max({x.l, y.l, x.a - y.b}), std::max({x.r, y.r, y.a - x.b}),
            std::max({x.m, y.m, x.l + y.a, y.r + x.a})};
}

void SegTree::build(int x, int l, int r) {
    if (l == r) {
        tree[x] = {A[l], B[l], INF, INF, INF};
        return;
    }
    const auto mid = (l + r) >> 1;
    build(lc, l, mid);
    build(rc, mid + 1, r);
    tree[x] = seg_merge(tree[lc], tree[rc]);
}

SegTree::SegTree(const int n) {
    for (int i = 1; i <= n; i++) {
        read(A[i]);
    }
    for (int i = 1; i <= n; i++) {
        read(B[i]);
    }
    build(1, 1, n);
}

void SegTree::mod(int x, int l, int r, const int& mk, const int& mv,
                  const int& mo) {
    if (l == r) {
        if (mo == 1) {
            tree[x].a = mv;
        } else if (mo == 2) {
            tree[x].b = mv;
        }
        return;
    }
    const auto mid = (l + r) >> 1;
    if (mk <= mid) {
        mod(lc, l, mid, mk, mv, mo);
    } else if (mid < mk) {
        mod(rc, mid + 1, r, mk, mv, mo);
    }
    tree[x] = seg_merge(tree[lc], tree[rc]);
}

SegTree::Node SegTree::query(int x, int l, int r, const int& ql,
                             const int& qr) {
    if (ql <= l and r <= qr) {
        return tree[x];
    }
    const auto mid = (l + r) >> 1;
    if (qr <= mid) {
        return query(lc, l, mid, ql, qr);
    }
    if (mid < ql) {
        return query(rc, mid + 1, r, ql, qr);
    }
    return seg_merge(query(lc, l, mid, ql, qr), query(rc, mid + 1, r, ql, qr));
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