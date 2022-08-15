#include <cmath>
#include <cstdio>
#include <iomanip>
#include <iostream>
#include <memory>

using ll = long long;

constexpr int MAX_N = 200050;

class SegTree {
   protected:
    struct {
        double s;
        double c;
        ll t;
    } tree[MAX_N << 2];

    void seg_merge(const int& x);

    void pushdown(const int& x);

    void build(int x, int l, int r);

   public:
    SegTree() = default;
    SegTree(const int n) { this->build(1, 1, n); }
    ~SegTree() = default;

    void mod(int x, int l, int r, const int& ml, const int& mr, const int& mv);

    double query(int x, int l, int r, const int& ql, const int& qr);
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

    int n;
    read(n);
    for (int i = 1; i <= n; i++) {
        read(a[i]);
    }
    auto segTree = std::make_unique<SegTree>(n);

    int m;
    read(m);
    while (m--) {
        int op;
        read(op);
        if (op == 1) {
            int x, y, z;
            read(x, y, z);
            segTree->mod(1, 1, n, x, y, z);
        } else if (op == 2) {
            int x, y;
            read(x, y);
            std::cout << std::fixed << std::setprecision(1)
                      << segTree->query(1, 1, n, x, y) << '\n';
        }
    }

    return 0;
}

#define lc (x << 1)
#define rc ((x << 1) | 1)

void SegTree::seg_merge(const int& x) {
    tree[x].s = tree[lc].s + tree[rc].s;
    tree[x].c = tree[lc].c + tree[rc].c;
}

void SegTree::pushdown(const int& x) {
    if (tree[x].t) {
        const auto st = std::sin(tree[x].t), ct = std::cos(tree[x].t);
        tree[lc] = {tree[lc].s * ct + tree[lc].c * st,
                    tree[lc].c * ct - tree[lc].s * st, tree[lc].t + tree[x].t};
        tree[rc] = {tree[rc].s * ct + tree[rc].c * st,
                    tree[rc].c * ct - tree[rc].s * st, tree[rc].t + tree[x].t};
        tree[x].t = 0;
    }
}

void SegTree::build(int x, int l, int r) {
    if (l == r) {
        tree[x] = {std::sin(a[l]), std::cos(a[l]), 0};
        return;
    }
    const auto mid = (l + r) >> 1;
    build(lc, l, mid);
    build(rc, mid + 1, r);
    seg_merge(x);
}

void SegTree::mod(int x, int l, int r, const int& ml, const int& mr,
                  const int& mv) {
    if (ml <= l and r <= mr) {
        tree[x] = {tree[x].s * std::cos(mv) + tree[x].c * std::sin(mv),
                   tree[x].c * std::cos(mv) - tree[x].s * std::sin(mv),
                   tree[x].t + mv};
        return;
    }
    const auto mid = (l + r) >> 1;
    pushdown(x);
    if (ml <= mid) {
        mod(lc, l, mid, ml, mr, mv);
    }
    if (mid < mr) {
        mod(rc, mid + 1, r, ml, mr, mv);
    }
    seg_merge(x);
}

double SegTree::query(int x, int l, int r, const int& ql, const int& qr) {
    if (ql <= l and r <= qr) {
        return tree[x].s;
    }
    const auto mid = (l + r) >> 1;
    double res{};
    pushdown(x);
    if (ql <= mid) {
        res += query(lc, l, mid, ql, qr);
    }
    if (mid < qr) {
        res += query(rc, mid + 1, r, ql, qr);
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