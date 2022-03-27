#include <cstdio>
#include <iostream>

typedef long long ll;

constexpr int MAX_N = 300050;

class SegTree {
   protected:
    struct Node {
        int l;
        int r;
        int le;
        int ic;
        int dc;
        int la;
        int ra;
        int an;
        ll tg;
        ll lk;
        ll rk;
    } tree[MAX_N << 2];

    int* A;

    void seg_merge(const int& x);

    void pushdown(const int& x);

    void build(int x, int l, int r);

   public:
    SegTree(const int& n, int* A) {
        this->A = A;
        build(1, 1, n);
    }
    ~SegTree() = default;

    void mod(int x, const int& ml, const int& mr, const ll& mv);

    const int& query() const { return tree[1].an; }
};

template <typename T>
T read();

int main() {
    std::ios::sync_with_stdio(false);

    int n = read<int>();
    auto* A = new int[n + 10];
    for (int i = 1; i <= n; i++) {
        A[i] = read<int>();
    }

    auto* segTree = new SegTree(n, A);
    int m = read<int>();
    while (m--) {
        int l = read<int>(), r = read<int>(), d = read<int>();
        segTree->mod(1, l, r, d);
        std::cout << segTree->query() << '\n';
    }

    return 0;
}

#define lc x * 2
#define rc x * 2 + 1

void SegTree::seg_merge(const int& x) {
    tree[x].lk = tree[lc].lk;
    tree[x].rk = tree[rc].rk;

    tree[x].ic = tree[rc].ic;
    if (tree[rc].ic == tree[rc].le and tree[rc].lk > tree[lc].rk) {
        tree[x].ic += tree[lc].ic;
    }
    tree[x].dc = tree[lc].dc;
    if (tree[lc].dc == tree[lc].le and tree[lc].rk > tree[rc].lk) {
        tree[x].dc += tree[rc].dc;
    }

    tree[x].la = tree[lc].la;
    if (tree[lc].ic == tree[lc].le) {
        if (tree[lc].rk < tree[rc].lk) {
            tree[x].la += tree[rc].la;
        }
        if (tree[lc].rk > tree[rc].lk) {
            tree[x].la += tree[rc].dc;
        }
    } else if (tree[lc].la == tree[lc].le and tree[lc].rk > tree[rc].lk) {
        tree[x].la += tree[rc].dc;
    }
    tree[x].ra = tree[rc].ra;
    if (tree[rc].dc == tree[rc].le) {
        if (tree[rc].lk < tree[lc].rk) {
            tree[x].ra += tree[lc].ra;
        }
        if (tree[rc].lk > tree[lc].rk) {
            tree[x].ra += tree[lc].ic;
        }
    } else if (tree[rc].ra == tree[rc].le and tree[rc].lk > tree[lc].rk) {
        tree[x].ra += tree[lc].ic;
    }

    tree[x].an = std::max(tree[lc].an, tree[rc].an);
    if (tree[lc].rk < tree[rc].lk) {
        tree[x].an = std::max(tree[x].an, tree[lc].ic + tree[rc].la);
    }
    if (tree[lc].rk > tree[rc].lk) {
        tree[x].an = std::max(tree[x].an, tree[rc].dc + tree[lc].ra);
    }
}

void SegTree::pushdown(const int& x) {
    if (tree[x].tg) {
        tree[lc].lk += tree[x].tg;
        tree[lc].rk += tree[x].tg;
        tree[lc].tg += tree[x].tg;
        tree[rc].lk += tree[x].tg;
        tree[rc].rk += tree[x].tg;
        tree[rc].tg += tree[x].tg;
        tree[x].tg = 0;
    }
}

void SegTree::build(int x, int l, int r) {
    tree[x].l = l;
    tree[x].r = r;
    tree[x].le = r - l + 1;
    tree[x].lk = A[l];
    tree[x].rk = A[r];
    if (l == r) {
        tree[x].ic = tree[x].dc = tree[x].la = tree[x].ra = tree[x].an = 1;
        return;
    }
    int mid = (l + r) >> 1;
    build(lc, l, mid);
    build(rc, mid + 1, r);
    seg_merge(x);
}

void SegTree::mod(int x, const int& ml, const int& mr, const ll& mv) {
    if (ml <= tree[x].l and tree[x].r <= mr) {
        tree[x].lk += mv;
        tree[x].rk += mv;
        tree[x].tg += mv;
        return;
    }
    int mid = (tree[x].l + tree[x].r) >> 1;
    pushdown(x);
    if (ml <= mid) {
        mod(lc, ml, mr, mv);
    }
    if (mid < mr) {
        mod(rc, ml, mr, mv);
    }
    seg_merge(x);
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