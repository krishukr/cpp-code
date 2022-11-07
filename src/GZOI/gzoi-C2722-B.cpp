#include <algorithm>
#include <climits>
#include <cstdio>
#include <iostream>
#include <memory>

using ll = long long;

constexpr int MAX_N = 1000050;
constexpr int N = 1000000;
constexpr ll INF = LLONG_MAX >> 4;

int a[MAX_N], b[MAX_N];
struct Q {
    int p;
    int k;
    int i;
} q[MAX_N];

class SegTree {
   public:
    struct L {
        ll k;
        ll b = INF;
        L() = default;
        L(ll k, ll b) { this->k = k, this->b = b; }
        // fxxk C++11, we need C++14!

        ll operator()(const ll& x) { return k * x + b; }
    } tree[MAX_N << 3];

    SegTree() = default;
    ~SegTree() = default;

    void mod(int x, int l, int r, L mv);

    ll query(int x, int l, int r, const ll& qk);
};

ll ans[MAX_N];

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
        read(a[i], b[i]);
    }
    for (int i = 1; i <= m; i++) {
        read(q[i].p, q[i].k);
        q[i].i = i;
    }
    std::sort(q + 1, q + m + 1,
              [](const Q& x, const Q& y) { return x.p < y.p; });

    {
        std::unique_ptr<SegTree> segTree(new SegTree());
        ll sa{}, sb{};
        int i{1};
        for (int j = 1; j <= m; j++) {
            while (i <= n and i <= q[j].p) {
                segTree->mod(1, -N, N, {-sb, sa});
                sa += a[i];
                sb += b[i];
                i++;
            }
            ans[q[j].i] += sa - sb * q[j].k - segTree->query(1, -N, N, q[j].k);
        }
    }
    {
        std::unique_ptr<SegTree> segTree(new SegTree());
        ll sa{}, sb{};
        int i{n};
        for (int j = m; j >= 1; j--) {
            while (i >= 1 and i > q[j].p) {
                segTree->mod(1, -N, N, {-sb, sa});
                sa += a[i];
                sb += b[i];
                i--;
            }
            ans[q[j].i] += std::max(
                0ll, sa - sb * q[j].k - segTree->query(1, -N, N, q[j].k));
        }
    }

    for (int i = 1; i <= m; i++) {
        std::cout << ans[i] << '\n';
    }

    return 0;
}

#define lc (x << 1)
#define rc ((x << 1) | 1)

void SegTree::mod(int x, int l, int r, L mv) {
    const auto mid = (l + r) >> 1;
    if (tree[x](mid) >= mv(mid)) {
        std::swap(tree[x], mv);
    }
    if (l == r) {
        return;
    }
    if (tree[x](l) >= mv(l)) {
        mod(lc, l, mid, mv);
    } else if (tree[x](r) >= mv(r)) {
        mod(rc, mid + 1, r, mv);
    }
}

ll SegTree::query(int x, int l, int r, const ll& qk) {
    if (l == r) {
        return tree[x](qk);
    }
    const auto mid = (l + r) >> 1;
    if (qk <= mid) {
        return std::min(tree[x](qk), query(lc, l, mid, qk));
    } else {
        return std::min(tree[x](qk), query(rc, mid + 1, r, qk));
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