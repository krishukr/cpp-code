#include <cstdio>
#include <iostream>
#include <memory>

using ll = long long;

constexpr int MAX_N = 300050;
constexpr int INF = 0x3f3f3f3f;

class SegTree {
   public:
    struct Node {
        ll s;
        int mx;
        int mn;

        Node operator+(const Node& x) const {
            return {s + x.s, std::max(mx, x.mx), std::min(mn, x.mn)};
        }
    } tree[MAX_N << 2];

   protected:
    void seg_merge(const int& x);

    void build(int x, int l, int r);

   public:
    SegTree() = default;
    SegTree(const int n) { this->build(1, 1, n); }
    ~SegTree() = default;

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
    auto segTree = std::make_unique<SegTree>(n);

    int lac{};
    while (m--) {
        int op;
        read(op);
        if (op == 1) {
            int x, y;
            read(x, y);
            x ^= lac;
            y ^= lac;
            segTree->mod(1, 1, n, x, y);
        } else if (op == 2) {
            int x, y, z;
            read(x, y, z);
            x ^= lac;
            y ^= lac;
            z ^= lac;
            const auto qa = segTree->query(1, 1, n, x, y);
            if (qa.s == 1ll * (qa.mx + qa.mn) * (y - x + 1) / 2 and
                qa.mx - qa.mn == (y - x) * z) {
                lac++;
                std::cout << "Yes\n";
            } else {
                std::cout << "No\n";
            }
        }
    }

    return 0;
}

#define lc (x << 1)
#define rc ((x << 1) | 1)

void SegTree::seg_merge(const int& x) { tree[x] = tree[lc] + tree[rc]; }

void SegTree::build(int x, int l, int r) {
    if (l == r) {
        tree[x] = {a[l], a[l], a[l]};
        return;
    }
    const auto mid = (l + r) >> 1;
    build(lc, l, mid);
    build(rc, mid + 1, r);
    seg_merge(x);
}

void SegTree::mod(int x, int l, int r, const int& mk, const int& mv) {
    if (l == r) {
        tree[x] = {mv, mv, mv};
        return;
    }
    const auto mid = (l + r) >> 1;
    if (mk <= mid) {
        mod(lc, l, mid, mk, mv);
    }
    if (mid < mk) {
        mod(rc, mid + 1, r, mk, mv);
    }
    seg_merge(x);
}

SegTree::Node SegTree::query(int x, int l, int r, const int& ql,
                             const int& qr) {
    if (ql <= l and r <= qr) {
        return tree[x];
    }
    const auto mid = (l + r) >> 1;
    Node res{0, -INF, INF};
    if (ql <= mid) {
        res = res + query(lc, l, mid, ql, qr);
    }
    if (mid < qr) {
        res = res + query(rc, mid + 1, r, ql, qr);
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