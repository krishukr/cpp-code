#include <cstdio>
#include <iostream>
#include <memory>

constexpr int MAX_K = 55;
constexpr int MAX_N = 35050;

class SegTree {
   private:
    struct {
        int m;
        int t;
    } tree[MAX_N << 2];

    int* A;

    void build(int x, int l, int r);

    void seg_merge(const int& x);

    void pushdown(const int& x);

   public:
    SegTree() = delete;
    SegTree(int n, int* A) {
        this->A = A;
        build(1, 1, n);
    }
    ~SegTree() = default;

    void mod(int x, int l, int r, const int& ml, const int& mr, const int& mv);

    int query(int x, int l, int r, const int& ql, const int& qr);
};

int f[MAX_K][MAX_N];
int p[MAX_N], g[MAX_N];

template <typename T>
T read();

template <typename T>
void read(T& t);

template <typename T, typename... Args>
void read(T& t, Args&... rest);

int main() {
    std::ios::sync_with_stdio(false);

    int n, k;
    read(n, k);
    for (int i = 1; i <= n; i++) {
        int x;
        read(x);
        g[i] = p[x] + 1;
        p[x] = i;
    }
    for (int i = 1; i <= k; i++) {
        auto segTree = std::make_unique<SegTree>(n, f[i - 1]);
        for (int j = 1; j <= n; j++) {
            segTree->mod(1, 1, n, g[j], j, 1);
            f[i][j] = segTree->query(1, 1, n, 1, j);
        }
    }
    std::cout << f[k][n] << '\n';

    return 0;
}

#define lc (x << 1)
#define rc ((x << 1) | 1)

void SegTree::build(int x, int l, int r) {
    if (l == r) {
        tree[x].m = A[l - 1];
        return;
    }
    const auto mid = (l + r) >> 1;
    build(lc, l, mid);
    build(rc, mid + 1, r);
    seg_merge(x);
}

void SegTree::seg_merge(const int& x) {
    tree[x].m = std::max(tree[lc].m, tree[rc].m);
}

void SegTree::pushdown(const int& x) {
    if (tree[x].t) {
        tree[lc].m += tree[x].t;
        tree[lc].t += tree[x].t;
        tree[rc].m += tree[x].t;
        tree[rc].t += tree[x].t;
        tree[x].t = 0;
    }
}

void SegTree::mod(int x, int l, int r, const int& ml, const int& mr,
                  const int& mv) {
    if (ml <= l and r <= mr) {
        tree[x].m += mv;
        tree[x].t += mv;
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

int SegTree::query(int x, int l, int r, const int& ql, const int& qr) {
    if (ql <= l and r <= qr) {
        return tree[x].m;
    }
    const auto mid = (l + r) >> 1;
    int res{};
    pushdown(x);
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