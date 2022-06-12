#include <cstdio>
#include <iostream>
#include <memory>

using ll = long long;

constexpr int MAX_A = 1000050;
constexpr int MAX_N = 300050;

namespace P {

int pri[MAX_N];
bool isp[MAX_A];
ll f[MAX_A], g[MAX_A];

void init();

}  // namespace P

class SegTree {
   private:
    struct Node {
        ll a;
        ll m;
    } tree[MAX_N << 2];

    void seg_merge(const int& x);

    void build(int x, int l, int r);

   public:
    SegTree() = default;
    SegTree(const int n) { build(1, 1, n); }
    ~SegTree() = default;

    void mod(int x, int l, int r, const int& ml, const int& mr);

    ll query(int x, int l, int r, const int& ql, const int& qr);
};

template <typename T>
T read();

template <typename T>
void read(T& t);

template <typename T, typename... Args>
void read(T& t, Args&... rest);

int main() {
    std::ios::sync_with_stdio(false);

    P::init();
    int n, m;
    read(n, m);
    auto segTree = std::make_unique<SegTree>(n);

    while (m--) {
        int op, l, r;
        read(op, l, r);
        if (op == 1) {
            segTree->mod(1, 1, n, l, r);
        } else {
            std::cout << segTree->query(1, 1, n, l, r) << '\n';
        }
    }

    return 0;
}

void P::init() {
    int cnt{};
    f[1] = g[1] = 1;
    for (int i = 2; i <= MAX_A - 40; i++) {
        if (!isp[i]) {
            pri[++cnt] = i;
            f[i] = 1;
            g[i] = 2;
        }
        for (int j = 1; j <= cnt; j++) {
            if (i * pri[j] > MAX_A - 40) {
                break;
            }
            isp[i * pri[j]] = true;
            if (!(i % pri[j])) {
                f[i * pri[j]] = f[i] + 1;
                g[i * pri[j]] = (g[i]) * (f[i * pri[j]] + 1) / (f[i] + 1);
            } else {
                f[i * pri[j]] = 1;
                g[i * pri[j]] = g[i] * g[pri[j]];
            }
        }
    }
}

#define lc ((x << 1))
#define rc ((x << 1) + 1)

void SegTree::seg_merge(const int& x) {
    tree[x].a = tree[lc].a + tree[rc].a;
    tree[x].m = std::max(tree[lc].m, tree[rc].m);
}

void SegTree::build(int x, int l, int r) {
    if (l == r) {
        int a;
        read(a);
        tree[x].a = tree[x].m = a;
        return;
    }
    const auto mid = (l + r) >> 1;
    build(lc, l, mid);
    build(rc, mid + 1, r);
    seg_merge(x);
}

void SegTree::mod(int x, int l, int r, const int& ml, const int& mr) {
    if (tree[x].m <= 2) {
        return;
    }
    if (l == r) {
        tree[x].a = tree[x].m = P::g[tree[x].a];
        return;
    }
    const auto mid = (l + r) >> 1;
    if (ml <= mid) {
        mod(lc, l, mid, ml, mr);
    }
    if (mid < mr) {
        mod(rc, mid + 1, r, ml, mr);
    }
    seg_merge(x);
}

ll SegTree::query(int x, int l, int r, const int& ql, const int& qr) {
    if (ql <= l and r <= qr) {
        return tree[x].a;
    }
    const auto mid = (l + r) >> 1;
    decltype(Node::a) res{};
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