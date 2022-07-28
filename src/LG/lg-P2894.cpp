#include <algorithm>
#include <cstdio>
#include <iostream>
#include <memory>

class SegTree {
   private:
    constexpr static int MAX_N = 50050;

   protected:
    struct Node {
        int l;
        int r;
        int s;
        int t;
        int c;
    } tree[MAX_N << 2];

    void seg_merge(const int& x);

    void pushdown(const int& x);

    void build(int x, int l, int r);

   public:
    SegTree() = default;
    SegTree(const int n) { this->build(1, 1, n); }
    ~SegTree() = default;

    void mod(int x, int l, int r, const int& ml, const int& mr, const int& mv);

    int query(int x, int l, int r, const int& qk);

    bool prec(const int& x) { return tree[1].s < x; }
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
        int op;
        read(op);
        if (op == 1) {
            int x;
            read(x);
            if (segTree->prec(x)) {
                std::cout << 0 << '\n';
                continue;
            } else {
                const auto p = segTree->query(1, 1, n, x);
                std::cout << p << '\n';
                segTree->mod(1, 1, n, p, p + x - 1, 1);
            }
        } else if (op == 2) {
            int x, y;
            read(x, y);
            segTree->mod(1, 1, n, x, x + y - 1, 2);
        }
    }

    return 0;
}

#define lc (x << 1)
#define rc ((x << 1) + 1)

void SegTree::seg_merge(const int& x) {
    if (tree[lc].s == tree[lc].c) {
        tree[x].l = tree[lc].s + tree[rc].l;
    } else {
        tree[x].l = tree[lc].l;
    }
    if (tree[rc].s == tree[rc].c) {
        tree[x].r = tree[rc].s + tree[lc].r;
    } else {
        tree[x].r = tree[rc].r;
    }
    tree[x].s = std::max({tree[lc].s, tree[rc].s, tree[lc].r + tree[rc].l});
}

void SegTree::pushdown(const int& x) {
    if (!tree[x].t) {
        return;
    }
    if (tree[x].t == 1) {
        tree[lc] = {0, 0, 0, 1, tree[lc].c};
        tree[rc] = {0, 0, 0, 1, tree[rc].c};
    } else if (tree[x].t == 2) {
        tree[lc] = {tree[lc].c, tree[lc].c, tree[lc].c, 2, tree[lc].c};
        tree[rc] = {tree[rc].c, tree[rc].c, tree[rc].c, 2, tree[rc].c};
    }
    tree[x].t = 0;
}

void SegTree::build(int x, int l, int r) {
    tree[x] = {r - l + 1, r - l + 1, r - l + 1, 0, r - l + 1};
    if (l == r) {
        return;
    }
    const auto mid = (l + r) >> 1;
    build(lc, l, mid);
    build(rc, mid + 1, r);
}

void SegTree::mod(int x, int l, int r, const int& ml, const int& mr,
                  const int& mv) {
    if (ml <= l and r <= mr) {
        const auto t = mv == 1 ? 0 : tree[x].c;
        tree[x] = {t, t, t, mv, tree[x].c};
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

int SegTree::query(int x, int l, int r, const int& qk) {
    if (l == r) {
        return l;
    }
    const auto mid = (l + r) >> 1;
    pushdown(x);
    if (qk <= tree[lc].s) {
        return query(lc, l, mid, qk);
    } else if (qk <= tree[lc].r + tree[rc].l) {
        return mid - tree[lc].r + 1;
    } else {
        return query(rc, mid + 1, r, qk);
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