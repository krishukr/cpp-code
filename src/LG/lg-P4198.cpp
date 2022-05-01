#include <cstdio>
#include <iostream>
#include <memory>

class SegTree {
   private:
    constexpr static int MAX_N = 100050;

   protected:
    struct Node {
        int l;
        int r;
        int s;
        double m;
    } tree[MAX_N << 2];

    void build(int x, int l, int r);

    int solve(int x, const double& mv);

    void seg_merge(const int& x);

   public:
    SegTree() = default;
    SegTree(const int& n) { build(1, 1, n); }
    ~SegTree() = default;

    void mod(int x, const int& mk, const double& mv);

    int query() const { return tree[1].s; }
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
        int x, y;
        read(x, y);
        segTree->mod(1, x, y);
        std::cout << segTree->query() << '\n';
    }

    return 0;
}

#define lc x * 2
#define rc x * 2 + 1

void SegTree::build(int x, int l, int r) {
    tree[x].l = l;
    tree[x].r = r;
    if (l == r) {
        return;
    }
    const int mid = (l + r) >> 1;
    build(lc, l, mid);
    build(rc, mid + 1, r);
}

int SegTree::solve(int x, const double& mv) {
    if (tree[x].m <= mv) {
        return 0;
    }
    if (tree[x].l == tree[x].r) {
        return 1;
    }
    if (tree[lc].m <= mv) {
        return solve(rc, mv);
    }
    return solve(lc, mv) + tree[x].s - tree[lc].s;
}

void SegTree::seg_merge(const int& x) {
    tree[x].s = tree[lc].s + solve(rc, tree[lc].m);
    tree[x].m = std::max(tree[lc].m, tree[rc].m);
}

void SegTree::mod(int x, const int& mk, const double& mv) {
    if (tree[x].l == tree[x].r) {
        tree[x].m = mv / mk;
        tree[x].s = 1;
        return;
    }
    const int mid = (tree[x].l + tree[x].r) >> 1;
    if (mk <= mid) {
        mod(lc, mk, mv);
    } else {
        mod(rc, mk, mv);
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

template <typename T>
void read(T& t) {
    t = read<T>();
}

template <typename T, typename... Args>
void read(T& t, Args&... rest) {
    t = read<T>();
    read(rest...);
}