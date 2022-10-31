#include <algorithm>
#include <cmath>
#include <cstdio>
#include <iostream>
#include <memory>

constexpr int MAX_N = 10050;
constexpr int N = 20001;

struct {
    int l;
    int r;
    int h;
    int v;
} o[MAX_N], e[MAX_N];

class SegTree {
    struct {
        int a;
        int c;
        int t;
    } tree[MAX_N << 3];

    void pushdown(const int& x);

    void seg_merge(const int& x);

    void build(int x, int l, int r);

   public:
    SegTree() { build(1, 1, N); }
    ~SegTree() = default;

    void mod(int x, int l, int r, const int& ml, const int& mr, const int& mv);

    int query() const { return tree[1].a * (tree[1].c == 0); }
};

int n;
long long ans;

void solve();

template <typename T>
T read();

template <typename T>
void read(T& t);

template <typename T, typename... Args>
void read(T& t, Args&... rest);

int main() {
    std::ios::sync_with_stdio(false);

    read(n);
    for (int i = 1; i <= n; i++) {
        int a, b, c, d;
        read(a, b, c, d);
        a += 10001, b += 10001, c += 10001, d += 10001;
        o[i] = {a, b, c, d};
        e[i + i - 1] = {a, c - 1, b, 1};
        e[i + i] = {a, c - 1, d, -1};
    }
    solve();

    for (int i = 1; i <= n; i++) {
        e[i + i - 1] = {o[i].r, o[i].v - 1, o[i].l, 1};
        e[i + i] = {o[i].r, o[i].v - 1, o[i].h, -1};
    }
    solve();

    std::cout << ans << '\n';

    return 0;
}

#define lc (x << 1)
#define rc ((x << 1) | 1)

void SegTree::pushdown(const int& x) {
    if (tree[x].t) {
        tree[lc].t += tree[x].t;
        tree[lc].c += tree[x].t;
        tree[rc].t += tree[x].t;
        tree[rc].c += tree[x].t;
        tree[x].t = 0;
    }
}

void SegTree::seg_merge(const int& x) {
    if (tree[lc].c == tree[rc].c) {
        tree[x].c = tree[lc].c;
        tree[x].a = tree[lc].a + tree[rc].a;
    } else if (tree[lc].c < tree[rc].c) {
        tree[x].c = tree[lc].c;
        tree[x].a = tree[lc].a;
    } else {
        tree[x].c = tree[rc].c;
        tree[x].a = tree[rc].a;
    }
}

void SegTree::build(int x, int l, int r) {
    if (l == r) {
        tree[x].a = 1;
        return;
    }
    const auto mid = (l + r) >> 1;
    build(lc, l, mid);
    build(rc, mid + 1, r);
    seg_merge(x);
}

void SegTree::mod(int x, int l, int r, const int& ml, const int& mr,
                  const int& mv) {
    if (ml <= l and r <= mr) {
        tree[x].c += mv;
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

#undef lc
#undef rc

void solve() {
    std::sort(e + 1, e + n + n + 1, [](const auto& x, const auto& y) {
        return x.h == y.h ? x.v > y.v : x.h < y.h;
    });
    auto segTree = std::make_unique<SegTree>();
    for (int i = 1; i <= n + n; i++) {
        const auto la = segTree->query();
        segTree->mod(1, 1, N, e[i].l, e[i].r, e[i].v);
        ans += std::abs(la - segTree->query());
    }
}

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