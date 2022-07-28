#include <algorithm>
#include <cstdio>
#include <iostream>
#include <memory>

constexpr int MAX_N = 500050;

class SegTree {
   public:
    struct Node {
        int l;
        int r;
        int m;
        int s;
    } tree[MAX_N << 2];

   protected:
    Node seg_merge(const Node& ln, const Node& rn);

    void build(int x, int l, int r);

   public:
    SegTree() = default;
    SegTree(const int n) { this->build(1, 1, n); }
    ~SegTree() = default;

    void mod(int x, int l, int r, const int& mk, const int& mv);

    Node query(int x, int l, int r, const int& ql, const int& qr);
};

int A[MAX_N];

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
        read(A[i]);
    }
    auto segTree = std::make_unique<SegTree>(n);

    while (m--) {
        int op, x, y;
        read(op, x, y);
        if (op == 1) {
            if (x > y) {
                std::swap(x, y);
            }
            std::cout << segTree->query(1, 1, n, x, y).m << '\n';
        } else if (op == 2) {
            segTree->mod(1, 1, n, x, y);
        }
    }

    return 0;
}

#define lc (x << 1)
#define rc ((x << 1) + 1)

SegTree::Node SegTree::seg_merge(const Node& ln, const Node& rn) {
    int tm{};
    if (ln.r < 0 and rn.l < 0) {
        tm = std::max(ln.r, rn.l);
    } else {
        if (ln.r > 0) {
            tm += ln.r;
        }
        if (rn.l > 0) {
            tm += rn.l;
        }
    }

    return {std::max(ln.l, ln.s + rn.l), std::max(rn.r, rn.s + ln.r),
            std::max({tm, ln.m, rn.m}), ln.s + rn.s};
}

void SegTree::build(int x, int l, int r) {
    if (l == r) {
        tree[x] = {A[l], A[l], A[l], A[l]};
        return;
    }
    const auto mid = (l + r) >> 1;
    build(lc, l, mid);
    build(rc, mid + 1, r);
    tree[x] = seg_merge(tree[lc], tree[rc]);
}

void SegTree::mod(int x, int l, int r, const int& mk, const int& mv) {
    if (l == r) {
        tree[x] = {mv, mv, mv, mv};
        return;
    }
    const auto mid = (l + r) >> 1;
    if (mk <= mid) {
        mod(lc, l, mid, mk, mv);
    } else {
        mod(rc, mid + 1, r, mk, mv);
    }
    tree[x] = seg_merge(tree[lc], tree[rc]);
}

SegTree::Node SegTree::query(int x, int l, int r, const int& ql,
                             const int& qr) {
    if (ql <= l and r <= qr) {
        return tree[x];
    }
    const auto mid = (l + r) >> 1;
    if (ql <= mid and mid < qr) {
        return seg_merge(query(lc, l, mid, ql, qr),
                         query(rc, mid + 1, r, ql, qr));
    } else if (ql <= mid) {
        return query(lc, l, mid, ql, qr);
    } else {
        return query(rc, mid + 1, r, ql, qr);
    }
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