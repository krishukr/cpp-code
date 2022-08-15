#include <cstdio>
#include <iostream>
#include <memory>

using ll = long long;

constexpr int MAX_N = 1000050;
constexpr int M = 1e9 + 50;

class SegTree {
   protected:
    struct {
        int l;
        int r;
        int z;
        ll s;
    } tree[5200000];

    int cnt;

    void seg_merge(const int& x);

   public:
    SegTree() = default;
    ~SegTree() = default;

    int root;

    void mod(int& x, int l, int r, const int& mk, const int& mv);

    int query_z(int x, int l, int r, const int& ql, const int& qr);

    ll query_s(int x, int l, int r, const int& ql, const int& qr);
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
    auto segTree = std::make_unique<SegTree>();
    segTree->mod(segTree->root, 0, M, 0, 0);

    while (m--) {
        char op = getchar();
        while (op != 'U' and op != 'Z') {
            op = getchar();
        }
        int x, y;
        read(x, y);
        if (op == 'U') {
            segTree->mod(segTree->root, 0, M, a[x], -1);
            a[x] = y;
            segTree->mod(segTree->root, 0, M, a[x], 1);
        } else if (op == 'Z') {
            const auto s =
                y > 0 ? segTree->query_s(segTree->root, 0, M, 0, y - 1) : 0;
            std::cout
                << ((ll)(x - segTree->query_z(segTree->root, 0, M, y, M)) * y <=
                            s
                        ? "TAK"
                        : "NIE")
                << '\n';
        }
    }

    return 0;
}

#define lc (tree[x].l)
#define rc (tree[x].r)

void SegTree::seg_merge(const int& x) {
    tree[x].z = tree[lc].z + tree[rc].z;
    tree[x].s = tree[lc].s + tree[rc].s;
}

void SegTree::mod(int& x, int l, int r, const int& mk, const int& mv) {
    if (!x) {
        x = ++cnt;
    }
    if (l == r) {
        tree[x].z += mv;
        tree[x].s += 1ll * mv * l;
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

int SegTree::query_z(int x, int l, int r, const int& ql, const int& qr) {
    if (!x) {
        return 0;
    }
    if (ql <= l and r <= qr) {
        return tree[x].z;
    }
    const auto mid = (l + r) >> 1;
    int res{};
    if (ql <= mid) {
        res += query_z(lc, l, mid, ql, qr);
    }
    if (mid < qr) {
        res += query_z(rc, mid + 1, r, ql, qr);
    }
    return res;
}

ll SegTree::query_s(int x, int l, int r, const int& ql, const int& qr) {
    if (!x) {
        return 0;
    }
    if (ql <= l and r <= qr) {
        return tree[x].s;
    }
    const auto mid = (l + r) >> 1;
    ll res{};
    if (ql <= mid) {
        res += query_s(lc, l, mid, ql, qr);
    }
    if (mid < qr) {
        res += query_s(rc, mid + 1, r, ql, qr);
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