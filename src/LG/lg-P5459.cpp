#include <cstdio>
#include <iostream>

typedef long long ll;

const ll INF = 1e10;
const int MAX_N = 100050;

ll p[MAX_N];

class SegTree {
   protected:
    struct Node {
        int l;
        int r;
        int s;
    } tree[MAX_N * (1 << 6)];

    int cnt;

    void seg_merge(int x) { tree[x].s = tree[tree[x].l].s + tree[tree[x].r].s; }

   public:
    SegTree() = default;
    ~SegTree() = default;

    int root;

    void mod_insert(int &x, const ll &p, ll l = -INF, ll r = INF) {
        if (!x) {
            x = ++cnt;
        }
        if (l == r) {
            tree[x].s++;
            return;
        }

        ll mid = (l + r) >> 1;
        if (p <= mid) {
            mod_insert(tree[x].l, p, l, mid);
        } else {
            mod_insert(tree[x].r, p, mid + 1, r);
        }
        seg_merge(x);
    }

    int query(int &x, const ll &ql, const ll &qr, ll l = -INF, ll r = INF) {
        if (!x) {
            x = ++cnt;
        }
        if (ql <= l and r <= qr) {
            return tree[x].s;
        }

        ll mid = (l + r) >> 1;
        ll res = 0;
        if (ql <= mid) {
            res += query(tree[x].l, ql, qr, l, mid);
        }
        if (qr > mid) {
            res += query(tree[x].r, ql, qr, mid + 1, r);
        }
        return res;
    }
};

template <typename T>
T read();

int main() {
    std::ios::sync_with_stdio(false);

    int n = read<int>(), l = read<int>(), r = read<int>();
    auto *segTree = new SegTree();
    for (int i = 1; i <= n; i++) {
        int x = read<int>();
        p[i] = p[i - 1] + x;
    }
    segTree->mod_insert(segTree->root, 0);

    ll ans = 0;
    for (int i = 1; i <= n; i++) {
        ans += segTree->query(segTree->root, p[i] - r, p[i] - l);
        segTree->mod_insert(segTree->root, p[i]);
    }
    std::cout << ans << '\n';

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
