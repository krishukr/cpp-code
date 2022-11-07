#include <climits>
#include <cstdio>
#include <iostream>
#include <memory>

using ll = long long;

constexpr int MAX_N = 100050;
constexpr int N = 1000000;
constexpr ll INF = LLONG_MAX >> 4;

class SegTree {
   public:
    struct L {
        ll k;
        ll b = INF;

        ll operator()(const ll& x) { return k * x + b; }
    } tree[(N + 50) << 2];

    SegTree() = default;
    ~SegTree() = default;

    void mod(int x, int l, int r, L mv);

    ll query(int x, int l, int r, const int& qk);
};

ll h[MAX_N], w[MAX_N], f[MAX_N];

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
        read(h[i]);
    }
    for (int i = 1; i <= n; i++) {
        read(w[i]);
        w[i] += w[i - 1];
    }

    auto segTree = std::make_unique<SegTree>();
    f[1] = 0;
    segTree->mod(1, 1, N, {-2 * h[1], f[1] + h[1] * h[1] - w[1]});
    for (int i = 2; i <= n; i++) {
        f[i] = segTree->query(1, 1, N, h[i]) + h[i] * h[i] + w[i - 1];
        segTree->mod(1, 1, N, {-2 * h[i], f[i] + h[i] * h[i] - w[i]});
    }
    std::cout << f[n] << '\n';

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

ll SegTree::query(int x, int l, int r, const int& qk) {
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