#include <algorithm>
#include <cstdio>
#include <iostream>
#include <memory>

using ll = long long;

constexpr int MAX_N = 50050;
constexpr int N = 50000;

class SegTree {
    struct {
        int s;
    } tree[MAX_N << 2];

    void seg_merge(const int& x);

   public:
    SegTree() = default;
    ~SegTree() = default;

    void mod(int x, int l, int r, const int& mk, const int& mv);

    int query(int x, int l, int r, const int& ql, const int& qr);
};

std::pair<int, int> o[MAX_N];

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
        read(o[i].first, o[i].second);
    }
    std::sort(o + 1, o + n + 1);

    std::unique_ptr<SegTree> segs(new SegTree()), segc(new SegTree());
    ll ans{};
    for (int i = 1; i <= n; i++) {
        const auto ls = segs->query(1, 1, N, 1, o[i].second),
                   lc = segc->query(1, 1, N, 1, o[i].second),
                   gs = segs->query(1, 1, N, o[i].second, N),
                   gc = segc->query(1, 1, N, o[i].second, N);
        ans += 1ll * o[i].first * (lc * o[i].second - ls) +
               1ll * o[i].first * (gs - gc * o[i].second);
        segs->mod(1, 1, N, o[i].second, o[i].second);
        segc->mod(1, 1, N, o[i].second, 1);
    }
    std::cout << ans << '\n';

    return 0;
}

#define lc (x << 1)
#define rc ((x << 1) | 1)

void SegTree::seg_merge(const int& x) { tree[x].s = tree[lc].s + tree[rc].s; }

void SegTree::mod(int x, int l, int r, const int& mk, const int& mv) {
    if (l == r) {
        tree[x].s += mv;
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
        return tree[x].s;
    }
    const auto mid = (l + r) >> 1;
    int res{};
    if (ql <= mid) {
        res += query(lc, l, mid, ql, qr);
    }
    if (mid < qr) {
        res += query(rc, mid + 1, r, ql, qr);
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