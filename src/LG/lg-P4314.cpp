#include <climits>
#include <cstdio>
#include <iostream>
#include <memory>

constexpr int MAX_N = 100050;

int a[MAX_N];

class SegTree {
   protected:
    struct Node {
        int t;
        int ht;
        int a;
        int ha;
        int m;
        int hm;
        bool vis;
    } tree[MAX_N << 2];

    void seg_merge(const int& x);

    void check_t(const int& x, const int& t, const int& ht);

    void check_a(const int& x, const int& a, const int& ha);

    void pushdown(const int& x);

    void build(int x, int l, int r);

   public:
    SegTree() = default;
    SegTree(int n) { build(1, 1, n); }
    ~SegTree() = default;

    void mod_add(int x, int l, int r, const int& ml, const int& mr,
                 const int& mv);

    void mod_set(int x, int l, int r, const int& ml, const int& mr,
                 const int& mv);

    int query_mx(int x, int l, int r, const int& ql, const int& qr);

    int query_hm(int x, int l, int r, const int& ql, const int& qr);
};

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
    int e;
    read(e);
    while (e--) {
        char op = getchar();
        while (op != 'Q' and op != 'A' and op != 'P' and op != 'C') {
            op = getchar();
        }
        int x, y;
        read(x, y);

        if (op == 'Q') {
            std::cout << segTree->query_mx(1, 1, n, x, y) << '\n';
        } else if (op == 'A') {
            std::cout << segTree->query_hm(1, 1, n, x, y) << '\n';
        } else if (op == 'P') {
            segTree->mod_add(1, 1, n, x, y, read<int>());
        } else if (op == 'C') {
            segTree->mod_set(1, 1, n, x, y, read<int>());
        }
    }

    return 0;
}

#define lc x * 2
#define rc x * 2 + 1

void SegTree::seg_merge(const int& x) {
    tree[x].m = std::max(tree[lc].m, tree[rc].m);
    tree[x].hm = std::max(tree[lc].hm, tree[rc].hm);
}

void SegTree::check_t(const int& x, const int& t, const int& ht) {
    tree[x].hm = std::max(tree[x].hm, tree[x].m + ht);
    tree[x].m += t;
    if (tree[x].vis) {
        tree[x].ha = std::max(tree[x].ha, tree[x].a + ht);
        tree[x].a += t;
    } else {
        tree[x].ht = std::max(tree[x].ht, tree[x].t + ht);
        tree[x].t += t;
    }
}

void SegTree::check_a(const int& x, const int& a, const int& ha) {
    tree[x].hm = std::max(tree[x].hm, ha);
    tree[x].m = tree[x].a = a;
    if (tree[x].vis) {
        tree[x].ha = std::max(tree[x].ha, ha);
    } else {
        tree[x].vis = true;
        tree[x].ha = ha;
    }
}

void SegTree::pushdown(const int& x) {
    check_t(lc, tree[x].t, tree[x].ht);
    check_t(rc, tree[x].t, tree[x].ht);
    tree[x].t = tree[x].ht = 0;

    if (tree[x].vis) {
        check_a(lc, tree[x].a, tree[x].ha);
        check_a(rc, tree[x].a, tree[x].ha);
        tree[x].a = tree[x].ha = 0;
        tree[x].vis = false;
    }
}

void SegTree::build(int x, int l, int r) {
    if (l == r) {
        tree[x].m = tree[x].hm = a[l];
        return;
    }
    int mid = (l + r) >> 1;
    build(lc, l, mid);
    build(rc, mid + 1, r);
    seg_merge(x);
}

void SegTree::mod_add(int x, int l, int r, const int& ml, const int& mr,
                      const int& mv) {
    if (ml <= l and r <= mr) {
        check_t(x, mv, mv);
        return;
    }
    const int mid = (l + r) >> 1;
    pushdown(x);
    if (ml <= mid) {
        mod_add(lc, l, mid, ml, mr, mv);
    }
    if (mid < mr) {
        mod_add(rc, mid + 1, r, ml, mr, mv);
    }
    seg_merge(x);
}

void SegTree::mod_set(int x, int l, int r, const int& ml, const int& mr,
                      const int& mv) {
    if (ml <= l and r <= mr) {
        check_a(x, mv, mv);
        return;
    }
    const int mid = (l + r) >> 1;
    pushdown(x);
    if (ml <= mid) {
        mod_set(lc, l, mid, ml, mr, mv);
    }
    if (mid < mr) {
        mod_set(rc, mid + 1, r, ml, mr, mv);
    }
    seg_merge(x);
}

int SegTree::query_mx(int x, int l, int r, const int& ql, const int& qr) {
    if (ql <= l and r <= qr) {
        return tree[x].m;
    }
    const int mid = (l + r) >> 1;
    int res = INT_MIN;
    pushdown(x);
    if (ql <= mid) {
        res = std::max(res, query_mx(lc, l, mid, ql, qr));
    }
    if (mid < qr) {
        res = std::max(res, query_mx(rc, mid + 1, r, ql, qr));
    }
    return res;
}

int SegTree::query_hm(int x, int l, int r, const int& ql, const int& qr) {
    if (ql <= l and r <= qr) {
        return tree[x].hm;
    }
    const int mid = (l + r) >> 1;
    int res = INT_MIN;
    pushdown(x);
    if (ql <= mid) {
        res = std::max(res, query_hm(lc, l, mid, ql, qr));
    }
    if (mid < qr) {
        res = std::max(res, query_hm(rc, mid + 1, r, ql, qr));
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