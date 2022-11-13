#include <algorithm>
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

    int query(int x, int l, int r, const int& qk);
};

int a[MAX_N];

struct Q {
    int l;
    int r;
    int i;
} q[MAX_N];

int ans[MAX_N];

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
    for (int i = 1; i <= m; i++) {
        read(q[i].l, q[i].r);
        q[i].i = i;
    }
    std::sort(q + 1, q + m + 1, [](const Q& x, const Q& y) {
        return x.r == y.r ? x.l < y.l : x.r < y.r;
    });

    std::unique_ptr<SegTree> segTree(new SegTree());
    for (int i = 1, j = 0; i <= n; i++) {
        segTree->mod(1, 0, N, a[i], i);
        while (j < m and q[j + 1].r == i) {
            j++;
            ans[q[j].i] = segTree->query(1, 0, N, q[j].l);
        }
    }
    for (int i = 1; i <= m; i++) {
        std::cout << ans[i] << '\n';
    }

    return 0;
}

#define lc (x << 1)
#define rc ((x << 1) | 1)

void SegTree::seg_merge(const int& x) {
    tree[x].m = std::min(tree[lc].m, tree[rc].m);
}

void SegTree::mod(int x, int l, int r, const int& mk, const int& mv) {
    if (l == r) {
        tree[x].m = mv;
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

int SegTree::query(int x, int l, int r, const int& qk) {
    if (l == r) {
        return l;
    }
    const auto mid = (l + r) >> 1;
    if (tree[lc].m < qk) {
        return query(lc, l, mid, qk);
    } else {
        return query(rc, mid + 1, r, qk);
    }
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