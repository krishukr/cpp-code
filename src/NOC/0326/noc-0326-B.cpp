#include <cstdio>
#include <iostream>

typedef long long ll;

constexpr int MAX_N = 100050;

class SegTree {
   protected:
    struct Node {
        ll a;
        ll c;
    } tree[MAX_N << 2];

    void seg_merge(const int& x);

   public:
    SegTree() = default;
    ~SegTree() = default;

    void mod(int x, int l, int r, const int& mk, const int& mv);

    ll query(int x, int l, int r, const int& qk);
};

int a[MAX_N];

template <typename T>
T read();

int main() {
    std::ios::sync_with_stdio(false);

    int n = read<int>(), m = read<int>(), K = read<int>();
    for (int i = 1; i <= n; i++) {
        a[i] = read<int>();
    }

    auto* segTree = new SegTree();
    for (int i = 1; i <= m; i++) {
        segTree->mod(1, 0, 100000, a[i], 1);
    }

    auto ans = segTree->query(1, 0, 100000, K);
    for (int i = m + 1; i <= n; i++) {
        segTree->mod(1, 0, 100000, a[i - m], -1);
        segTree->mod(1, 0, 100000, a[i], 1);
        ans += segTree->query(1, 0, 100000, K);
    }
    std::cout << ans << '\n';

    return 0;
}

#define lc x * 2
#define rc x * 2 + 1

void SegTree::seg_merge(const int& x) {
    tree[x].a = tree[lc].a + tree[rc].a;
    tree[x].c = tree[lc].c + tree[rc].c;
}

void SegTree::mod(int x, int l, int r, const int& mk, const int& mv) {
    if (l == r) {
        tree[x].c += mv;
        tree[x].a += 1ll * l * mv;
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

ll SegTree::query(int x, int l, int r, const int& qk) {
    if (l == r) {
        return 1ll * l * qk;
    }
    int mid = (l + r) >> 1;
    int cl = tree[lc].c;
    if (qk <= cl) {
        return query(lc, l, mid, qk);
    } else {
        return tree[lc].a + query(rc, mid + 1, r, qk - cl);
    }
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