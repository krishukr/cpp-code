#include <cstdio>
#include <iostream>
#include <memory>

constexpr int MAX_N = 200050;
constexpr int N = 200000;

class SegTree {
    struct {
        int m;
    } tree[MAX_N << 2];

    void seg_merge(const int& x);

   public:
    SegTree() = default;
    ~SegTree() = default;

    void mod(int x, int l, int r, const int& mk, const int& mv);

    int query(int x, int l, int r, const int& ql, const int& qr);
};

template <typename T>
T read();

template <typename T>
void read(T& t);

template <typename T, typename... Args>
void read(T& t, Args&... rest);

template <>
char read();

int main() {
    std::ios::sync_with_stdio(false);

    std::unique_ptr<SegTree> segTree(new SegTree());
    int n, p, l{}, c{};
    read(n, p);
    while (n--) {
        char op;
        int x;
        read(op, x);
        if (op == 'A') {
            x = (1ll * l + x) % p;
            segTree->mod(1, 1, N, ++c, x);
        } else if (op == 'Q') {
            std::cout << (l = segTree->query(1, 1, N, c - x + 1, c)) << '\n';
        }
    }

    return 0;
}

#define lc (x << 1)
#define rc ((x << 1) | 1)

void SegTree::seg_merge(const int& x) {
    tree[x].m = std::max(tree[lc].m, tree[rc].m);
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
    int res{};
    if (ql <= mid) {
        res = std::max(res, query(lc, l, mid, ql, qr));
    }
    if (mid < qr) {
        res = std::max(res, query(rc, mid + 1, r, ql, qr));
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

template <>
char read() {
    char ch = getchar_unlocked();
    while (ch != 'A' and ch != 'Q') {
        ch = getchar_unlocked();
    }
    return ch;
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