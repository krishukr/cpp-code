#include <climits>
#include <cstdio>
#include <iostream>
#include <memory>

using ll = long long;

constexpr int MAX_N = 100050;

class SegTree {
   protected:
    struct {
        ll m;
        ll t;
    } tree[MAX_N << 2];

    void seg_merge(const int& x);

    void pushdown(const int& x);

   public:
    SegTree() = default;
    ~SegTree() = default;

    void mod(int x, int l, int r, const int& ml, const int& mr, const ll& mv);

    ll query(int x, int l, int r, const int& ql, const int& qr);
};

int a[MAX_N];
ll s[MAX_N], f[MAX_N];
int s1[MAX_N], s2[MAX_N];
int t1, t2;

template <typename T>
T read();

template <typename T>
void read(T& t);

template <typename T, typename... Args>
void read(T& t, Args&... rest);

signed main() {
    std::ios::sync_with_stdio(false);

    int n, W;
    read(n, W);
    for (int i = 1; i <= n; i++) {
        read(a[i]);
    }
    for (int i = n; i >= 1; i--) {
        s[i] = s[i + 1] + a[i];
    }

    auto segTree = std::make_unique<SegTree>();
    int p{1};
    for (int i = 1; i <= n; i++) {
        while (s[p] - s[i + 1] > W) {
            p++;
        }
        while (t1 and a[i] < a[s1[t1]] and s1[t1] >= p) {
            segTree->mod(1, 1, n, s1[t1 - 1] + 1, s1[t1], a[s1[t1]]);
            t1--;
        }
        while (t2 and a[i] > a[s2[t2]] and s2[t2] >= p) {
            segTree->mod(1, 1, n, s2[t2 - 1] + 1, s2[t2], -a[s2[t2]]);
            t2--;
        }
        segTree->mod(1, 1, n, s1[t1] + 1, i - 1, -a[i]);
        segTree->mod(1, 1, n, s2[t2] + 1, i - 1, a[i]);
        segTree->mod(1, 1, n, i, i, f[i - 1] + s[i]);
        f[i] = segTree->query(1, 1, n, p, i);
        s1[++t1] = i;
        s2[++t2] = i;
    }
    std::cout << f[n] << '\n';

    return 0;
}

#define lc (x << 1)
#define rc ((x << 1) | 1)

void SegTree::seg_merge(const int& x) {
    tree[x].m = std::min(tree[lc].m, tree[rc].m);
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
                  const ll& mv) {
    if (ml > mr) {
        return;
    }
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

ll SegTree::query(int x, int l, int r, const int& ql, const int& qr) {
    if (ql > qr) {
        return 0;
    }
    if (ql <= l and r <= qr) {
        return tree[x].m;
    }
    const auto mid = (l + r) >> 1;
    ll res = LLONG_MAX;
    pushdown(x);
    if (ql <= mid) {
        res = std::min(res, query(lc, l, mid, ql, qr));
    }
    if (mid < qr) {
        res = std::min(res, query(rc, mid + 1, r, ql, qr));
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