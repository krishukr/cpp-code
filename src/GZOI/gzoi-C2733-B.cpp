#include <cstdio>
#include <iostream>
#include <memory>

using ll = long long;

constexpr int MAX_N = 100050;

class SegTree {
    struct {
        ll t;
        ll a;
        ll c;
    } tree[MAX_N << 2];

    void seg_merge(const int& x);

    void pushdown(const int& x);

    void build(int x, int l, int r);

    int* A;
    int* B;

   public:
    SegTree() = default;
    SegTree(const int n, int* A, int* B) {
        this->A = A;
        this->B = B;
        build(1, 1, n);
    }
    ~SegTree() = default;

    void mod(int x, int l, int r, const int& ml, const int& mr);

    ll query(int x, int l, int r, const int& ql, const int& qr);
};

int a[MAX_N], b[MAX_N];

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
    for (int i = 1; i <= n; i++) {
        read(b[i]);
    }
    std::unique_ptr<SegTree> segTree(new SegTree(n, a, b));

    while (m--) {
        int op;
        read(op);
        if (op == 1) {
            int x;
            read(x);
            segTree->mod(1, 1, n, x, x);
        } else if (op == 2) {
            int x, y;
            read(x, y);
            segTree->mod(1, 1, n, x, y);
        } else if (op == 3) {
            int x, y;
            read(x, y);
            std::cout << segTree->query(1, 1, n, x, y) << '\n';
        }
    }

    return 0;
}

#define lc (x << 1)
#define rc ((x << 1) | 1)

void SegTree::seg_merge(const int& x) {
    tree[x].a = tree[lc].a + tree[rc].a;
    tree[x].c = tree[lc].c + tree[rc].c;
}

void SegTree::pushdown(const int& x) {
    if (tree[x].t) {
        tree[lc].t ^= tree[x].t;
        tree[lc].c = tree[lc].a - tree[lc].c;
        tree[rc].t ^= tree[x].t;
        tree[rc].c = tree[rc].a - tree[rc].c;
        tree[x].t = 0;
    }
}

void SegTree::build(int x, int l, int r) {
    if (l == r) {
        tree[x].a = B[l];
        if (A[l]) {
            tree[x].t = 1;
            tree[x].c = tree[x].a;
        }
        return;
    }
    const auto mid = (l + r) >> 1;
    build(lc, l, mid);
    build(rc, mid + 1, r);
    seg_merge(x);
}

void SegTree::mod(int x, int l, int r, const int& ml, const int& mr) {
    if (ml <= l and r <= mr) {
        tree[x].t ^= 1;
        tree[x].c = tree[x].a - tree[x].c;
        return;
    }
    pushdown(x);
    const auto mid = (l + r) >> 1;
    if (ml <= mid) {
        mod(lc, l, mid, ml, mr);
    }
    if (mid < mr) {
        mod(rc, mid + 1, r, ml, mr);
    }
    seg_merge(x);
}

ll SegTree::query(int x, int l, int r, const int& ql, const int& qr) {
    if (ql <= l and r <= qr) {
        return tree[x].c;
    }
    pushdown(x);
    const auto mid = (l + r) >> 1;
    ll res{};
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