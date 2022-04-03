#include <cstdio>
#include <iostream>

class SegTree {
   private:
    typedef long long ll;
    constexpr static int MAX_N = 200050;

   protected:
    struct Node {
        ll v;
        int lc;
        int rc;
    } tree[MAX_N << 5];

    int pool[MAX_N << 5];
    int coll, used;

    int get_node() { return coll ? pool[coll--] : ++used; }
    void del_node(const int& x) {
        pool[++coll] = x;
        tree[x] = {0, 0, 0};
    }

   public:
    SegTree() = default;
    ~SegTree() = default;

    int root[MAX_N];
    int cnt = 1;

    void mod(int& x, int l, int r, const int& mk, const int& mv);

    ll query_count(int x, int l, int r, const int& ql, const int& qr);

    int query_kth(int x, int l, int r, const int& qv);

    int tree_merge(const int& a, const int& b);

    void tree_split(int a, int& b, const ll& k);

    bool check(const int& x, const int& y) { return tree[root[x]].v < y; }
};

template <typename T>
T read();

int main() {
    std::ios::sync_with_stdio(false);

    int n = read<int>(), m = read<int>();
    auto* segTree = new SegTree();
    for (int i = 1; i <= n; i++) {
        int x = read<int>();
        segTree->mod(segTree->root[segTree->cnt], 1, n, i, x);
    }

    while (m--) {
        int op = read<int>();
        if (op == 0) {
            int p = read<int>(), x = read<int>(), y = read<int>();
            const auto a1 = segTree->query_count(segTree->root[p], 1, n, 1, y);
            const auto a2 = segTree->query_count(segTree->root[p], 1, n, x, y);
            int ea = 0;
            segTree->tree_split(segTree->root[p],
                                segTree->root[++(segTree->cnt)], a1 - a2);
            segTree->tree_split(segTree->root[segTree->cnt], ea, a2);
            segTree->root[p] = segTree->tree_merge(segTree->root[p], ea);
        } else if (op == 1) {
            int a = read<int>(), b = read<int>();
            segTree->root[a] =
                segTree->tree_merge(segTree->root[a], segTree->root[b]);
        } else if (op == 2) {
            int p = read<int>(), x = read<int>(), y = read<int>();
            segTree->mod(segTree->root[p], 1, n, y, x);
        } else if (op == 3) {
            int p = read<int>(), x = read<int>(), y = read<int>();
            std::cout << segTree->query_count(segTree->root[p], 1, n, x, y)
                      << '\n';
        } else if (op == 4) {
            int x = read<int>(), y = read<int>();
            if (segTree->check(x, y)) {
                std::cout << -1 << '\n';
            } else {
                std::cout << segTree->query_kth(segTree->root[x], 1, n, y)
                          << '\n';
            }
        }
    }

    return 0;
}

void SegTree::mod(int& x, int l, int r, const int& mk, const int& mv) {
    if (!x) {
        x = get_node();
    }
    tree[x].v += mv;

    if (l == r) {
        return;
    }
    int mid = (l + r) >> 1;
    if (mk <= mid) {
        mod(tree[x].lc, l, mid, mk, mv);
    } else {
        mod(tree[x].rc, mid + 1, r, mk, mv);
    }
}

SegTree::ll SegTree::query_count(int x, int l, int r, const int& ql,
                                 const int& qr) {
    if (qr < l or r < ql) {
        return 0;
    }
    if (ql <= l and r <= qr) {
        return tree[x].v;
    }
    int mid = (l + r) >> 1;
    return query_count(tree[x].lc, l, mid, ql, qr) +
           query_count(tree[x].rc, mid + 1, r, ql, qr);
}

int SegTree::query_kth(int x, int l, int r, const int& qv) {
    if (l == r) {
        return l;
    }
    const auto& lv = tree[tree[x].lc].v;
    int mid = (l + r) >> 1;
    if (qv <= lv) {
        return query_kth(tree[x].lc, l, mid, qv);
    } else {
        return query_kth(tree[x].rc, mid + 1, r, qv - lv);
    }
}

int SegTree::tree_merge(const int& a, const int& b) {
    if (!a or !b) {
        return a + b;
    }
    tree[a].v += tree[b].v;
    tree[a].lc = tree_merge(tree[a].lc, tree[b].lc);
    tree[a].rc = tree_merge(tree[a].rc, tree[b].rc);
    del_node(b);
    return a;
}

void SegTree::tree_split(int a, int& b, const ll& k) {
    if (!a) {
        return;
    }
    b = get_node();
    const auto& lv = tree[tree[a].lc].v;
    if (k > lv) {
        tree_split(tree[a].rc, tree[b].rc, k - lv);
    } else {
        std::swap(tree[a].rc, tree[b].rc);
    }
    if (k < lv) {
        tree_split(tree[a].lc, tree[b].lc, k);
    }

    tree[b].v = tree[a].v - k;
    tree[a].v = k;
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