#include <cstdio>
#include <iomanip>
#include <iostream>
#include <memory>

constexpr int MAX_N = 200050;

class SegTree {
    struct {
        int s;
    } tree[MAX_N << 2];

    void seg_merge(const int& x);

    void build(int x, int l, int r);

   public:
    SegTree() = default;
    SegTree(const int n) { build(1, 1, n); }
    ~SegTree() = default;

    void mod(int x, int l, int r, const int& mk);

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

    int n;
    read(n);
    for (int i = 1; i <= n; i++) {
        read(a[i]);
    }
    std::unique_ptr<SegTree> segTree(new SegTree(n));

    int m;
    read(m);
    while (m--) {
        int x, y;
        read(x, y);
        std::cout << std::fixed << std::setprecision(2)
                  << 3.14 * segTree->query(1, 1, n, x, y) << '\n';
        segTree->mod(1, 1, n, (x + y) >> 1);
    }

    return 0;
}

#define lc (x << 1)
#define rc ((x << 1) | 1)

void SegTree::seg_merge(const int& x) { tree[x].s = tree[lc].s + tree[rc].s; }

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

void SegTree::mod(int x, int l, int r, const int& mk) {
    if (l == r) {
        tree[x] = {0};
        return;
    }
    const auto mid = (l + r) >> 1;
    if (mk <= mid) {
        mod(lc, l, mid, mk);
    } else {
        mod(rc, mid + 1, r, mk);
    }
    seg_merge(x);
}

int SegTree::query(int x, int l, int r, const int& ql, const int& qr) {
    if (ql <= l and r <= qr) {
        return tree[x].s;
    }
    const auto mid = (l + r) >> 1;
    int ans{};
    if (ql <= mid) {
        ans += query(lc, l, mid, ql, qr);
    }
    if (mid < qr) {
        ans += query(rc, mid + 1, r, ql, qr);
    }
    return ans;
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