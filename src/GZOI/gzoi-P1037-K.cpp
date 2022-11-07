#include <climits>
#include <cstdio>
#include <iostream>
#include <memory>

constexpr int MAX_N = 60050;

class SegTree {
    struct {
        int t;
        int m;
    } tree[MAX_N << 2];

    void pushdown(const int& x);

    void seg_merge(const int& x);

   public:
    SegTree() = default;
    ~SegTree() = default;

    void mod(int x, int l, int r, const int& ml, const int& mr, const int& mv);

    int query(int x, int l, int r, const int& ql, const int& qr);
};

template <typename T>
T read();

template <typename T>
void read(T& t);

template <typename T, typename... Args>
void read(T& t, Args&... rest);

int main() {
    std::ios::sync_with_stdio(false);

    int n, s, r;
    read(n, s, r);
    std::unique_ptr<SegTree> segTree(new SegTree());
    segTree->mod(1, 1, n, 1, n, s);

    while (r--) {
        int x, y, z;
        read(x, y, z);
        y--;
        if (segTree->query(1, 1, n, x, y) >= z) {
            std::cout << "YES" << '\n';
            segTree->mod(1, 1, n, x, y, -z);
        } else {
            std::cout << "NO" << '\n';
        }
    }

    return 0;
}

#define lc (x << 1)
#define rc ((x << 1) | 1)

void SegTree::pushdown(const int& x) {
    if (tree[x].t) {
        tree[lc].t += tree[x].t;
        tree[lc].m += tree[x].t;
        tree[rc].t += tree[x].t;
        tree[rc].m += tree[x].t;
        tree[x].t = 0;
    }
}

void SegTree::seg_merge(const int& x) {
    tree[x].m = std::min(tree[lc].m, tree[rc].m);
}

void SegTree::mod(int x, int l, int r, const int& ml, const int& mr,
                  const int& mv) {
    if (ml <= l and r <= mr) {
        tree[x].t += mv;
        tree[x].m += mv;
        return;
    }
    pushdown(x);
    const auto mid = (l + r) >> 1;
    if (ml <= mid) {
        mod(lc, l, mid, ml, mr, mv);
    }
    if (mid < mr) {
        mod(rc, mid + 1, r, ml, mr, mv);
    }
    seg_merge(x);
}

int SegTree::query(int x, int l, int r, const int& ql, const int& qr) {
    if (ql <= l and r <= qr) {
        return tree[x].m;
    }
    pushdown(x);
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