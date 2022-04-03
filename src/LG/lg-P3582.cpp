#include <cstdio>
#include <iostream>

typedef long long ll;

constexpr int MAX_N = 1000050;

int f[MAX_N], pre[MAX_N], lst[MAX_N];
int v[MAX_N];

class SegTree {
   protected:
    struct Node {
        ll la;
        ll ra;
        ll a;
        ll s;
    } tree[MAX_N * 3];

    void seg_merge(const int& x);

   public:
    SegTree() = default;
    ~SegTree() = default;

    void mod(int x, int l, int r, const int& mk, const int& mv);

    const ll& query() const { return tree[1].a; }
};

template <typename T = int>
T read();

int main() {
    std::ios::sync_with_stdio(false);

    int n = read<int>(), m = read<int>();
    for (int i = 1; i <= n; i++) {
        f[i] = read();
    }
    for (int i = 1; i <= m; i++) {
        v[i] = read();
    }

    auto* segTree = new SegTree();
    ll ans = 0;
    for (int i = 1; i <= n; i++) {
        pre[i] = lst[f[i]];
        lst[f[i]] = i;

        if (pre[i]) {
            segTree->mod(1, 1, n, pre[i], -v[f[i]]);
        }
        if (pre[pre[i]]) {
            segTree->mod(1, 1, n, pre[pre[i]], 0);
        }

        segTree->mod(1, 1, n, i, v[f[i]]);
        ans = std::max(ans, segTree->query());
    }

    std::cout << ans << '\n';

    return 0;
}

#define lc x * 2
#define rc x * 2 + 1

void SegTree::seg_merge(const int& x) {
    tree[x].s = tree[lc].s + tree[rc].s;
    tree[x].la = std::max(tree[lc].la, tree[lc].s + tree[rc].la);
    tree[x].ra = std::max(tree[rc].ra, tree[rc].s + tree[lc].ra);
    tree[x].a =
        std::max(tree[lc].ra + tree[rc].la, std::max(tree[lc].a, tree[rc].a));
}

void SegTree::mod(int x, int l, int r, const int& mk, const int& mv) {
    if (l == r) {
        tree[x] = {mv, mv, mv, mv};
        return;
    }
    int mid = (l + r) >> 1;
    if (mk <= mid) {
        mod(lc, l, mid, mk, mv);
    } else {
        mod(rc, mid + 1, r, mk, mv);
    }
    seg_merge(x);
}

#undef lc
#undef rc

template <typename T = int>
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