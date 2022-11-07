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

   private:
    Node seg_merge(const Node& l, const Node& r);

    void build(int x, int l, int r);

   public:
    SegTree() = default;
    SegTree(const int n) { build(1, 1, n); }

    void mod(int x, int l, int r, const int& mk, const int& mv);

    Node query(int x, int l, int r, const int& ql, const int& qr);
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
        int p, x, y;
        read(p, x, y);
        if (p == 1) {
            if (x > y) {
                std::swap(x, y);
            }
            std::cout << segTree->query(1, 1, n, x, y).m << '\n';
        } else if (p == 2) {
            segTree->mod(1, 1, n, x, y);
        }
    }

    return 0;
}

#define lc (x << 1)
#define rc ((x << 1) | 1)

SegTree::Node SegTree::seg_merge(const Node& l, const Node& r) {
    int m{};
    if (l.r < 0 and r.l < 0) {
        m = std::max(l.r, r.l);
    } else {
        if (l.r > 0) {
            m += l.r;
        }
        if (r.l > 0) {
            m += r.l;
        }
    }
    return {std::max(l.l, l.s + r.l), std::max(r.r, r.s + l.r),
            std::max({m, l.m, r.m}), l.s + r.s};
}

void SegTree::build(int x, int l, int r) {
    if (l == r) {
        tree[x] = {a[l], a[l], a[l], a[l]};
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
    } else if (mid < qr) {
        return query(rc, mid + 1, r, ql, qr);
    } else {
        return {};
    }
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