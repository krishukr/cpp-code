#include <cstdio>
#include <iostream>

typedef long long ll;

constexpr int MAX_N = 200050;

int a[MAX_N], h[MAX_N];
ll sum[MAX_N];

class SegTree {
   private:
    constexpr static ll INF = 0x3f3f3f3f3f3f3f3f;

   protected:
    struct Node {
        ll m;
        ll n;
        ll a;

        Node operator+(const Node& x) const {
            return {std::max(m, x.m), std::max(n, x.n),
                    std::max(n + x.m, std::max(a, x.a))};
        }
    } tree[MAX_N << 2];

#define lc x * 2
#define rc x * 2 + 1

    void build(int x, int l, int r) {
        if (l == r) {
            tree[x].a = -INF;
            tree[x].m = sum[l - 1] + 2ll * h[l];
            tree[x].n = 2ll * h[l] - sum[l - 1];
            return;
        }
        int mid = (l + r) >> 1;
        build(lc, l, mid);
        build(rc, mid + 1, r);
        tree[x] = tree[lc] + tree[rc];
    }

   public:
    SegTree(const int& n) { build(1, 1, n); };
    ~SegTree() = default;

    Node query(int x, int l, int r, const int& ql, const int& qr) {
        if (ql <= l and r <= qr) {
            return tree[x];
        }
        Node res{-INF, -INF, -INF};
        int mid = (l + r) >> 1;
        if (ql <= mid) {
            res = res + query(lc, l, mid, ql, qr);
        }
        if (mid < qr) {
            res = res + query(rc, mid + 1, r, ql, qr);
        }
        return res;
    }

#undef lc
#undef rc
};

template <typename T>
T read();

int main() {
    std::ios::sync_with_stdio(false);

    int n = read<int>(), m = read<int>();
    for (int i = 1; i <= n; i++) {
        a[i + n] = a[i] = read<int>();
    }
    for (int i = 1; i <= n; i++) {
        h[i + n] = h[i] = read<int>();
    }

    n = n + n;
    for (int i = 1; i <= n; i++) {
        sum[i] = sum[i - 1] + a[i];
    }
    auto* segTree = new SegTree(n);

    for (int i = 1; i <= m; i++) {
        int a = read<int>(), b = read<int>();
        std::cout << segTree
                         ->query(1, 1, n, b + 1,
                                 (a <= b ? (a + n / 2 - 1) : (a - 1)))
                         .a
                  << '\n';
    }

    return 0;
}

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