#include <algorithm>
#include <cstdio>
#include <iostream>
#include <vector>

constexpr int MAX_N = 500050;
constexpr int INF = 0x3f3f3f3f;

class SegTree {
   protected:
    struct Node {
        int l;
        int r;
        int s;
    } tree[MAX_N << 2];

#define lc x * 2
#define rc x * 2 + 1

    void seg_merge(const int& x) {
        tree[x].s = std::min(tree[lc].s, tree[rc].s);
    }

    void build(int x, int l, int r) {
        tree[x].l = l;
        tree[x].r = r;
        if (l == r) {
            return;
        }

        int mid = (l + r) >> 1;
        build(lc, l, mid);
        build(rc, mid + 1, r);
    }

   public:
    SegTree(const int& n) {
        std::fill(tree, tree + (n << 2), (Node){0, 0, INF});
        build(1, 1, n);
    }
    ~SegTree() = default;

    void mod(int x, const int& mk, const int& mv) {
        if (tree[x].l == tree[x].r) {
            tree[x].s = mv;
            return;
        }
        int mid = (tree[x].l + tree[x].r) >> 1;
        if (mk <= mid) {
            mod(lc, mk, mv);
        } else {
            mod(rc, mk, mv);
        }
        seg_merge(x);
    }

    int query(int x, const int& ql, const int& qr) {
        if (ql <= tree[x].l and tree[x].r <= qr) {
            return tree[x].s;
        }
        int mid = (tree[x].l + tree[x].r) >> 1;
        int res = INF;
        if (ql <= mid) {
            res = std::min(res, query(lc, ql, qr));
        }
        if (mid < qr) {
            res = std::min(res, query(rc, ql, qr));
        }
        return res;
    }

#undef lc
#undef rc
};

struct Que {
    int l;
    int idx;
};

std::vector<Que> q[MAX_N];

int a[MAX_N], b[MAX_N], pr[MAX_N], ps[MAX_N];
int ans[MAX_N];

template <typename T>
T read();

int main() {
    std::ios::sync_with_stdio(false);

    int n = read<int>(), m = read<int>();
    auto* segTree = new SegTree(n);
    for (int i = 1; i <= n; i++) {
        b[i] = a[i] = read<int>();
    }

    std::sort(b + 1, b + n + 1);
    int cnt = std::unique(b + 1, b + n + 1) - b - 1;
    for (int i = 1; i <= n; i++) {
        a[i] = std::lower_bound(b + 1, b + cnt + 1, a[i]) - b;
        pr[i] = ps[a[i]];
        ps[a[i]] = i;
    }

    for (int i = 1; i <= m; i++) {
        int x = read<int>(), y = read<int>();
        q[y].push_back({x, i});
    }

    for (int i = 1; i <= n; i++) {
        if (pr[i]) {
            segTree->mod(1, pr[i], i - pr[i]);
        }
        for (auto&& j : q[i]) {
            ans[j.idx] = segTree->query(1, j.l, i);
        }
    }

    for (int i = 1; i <= m; i++) {
        std::cout << (ans[i] == INF ? -1 : ans[i]) << '\n';
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