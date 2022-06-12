#include <cstdio>
#include <iostream>
#include <memory>

using ll = long long;

constexpr int MAX_N = 300050;

class SegTree {
   private:
    struct Node {
        int l;
        int r;
        ll a;
    } tree[MAX_N << 5];

    int cnt;

    int tree_merge(int a, int b);

    void mod(int& x, int l, int r, const int& mk, const int& mv);

   public:
    SegTree() = default;
    ~SegTree() = default;

    int root[MAX_N];

    void dfs(int x, int f);

    ll query(int x, int l, int r, const int& ql, const int& qr);
};

int n, q;

struct Node {
    int v;
    int nxt;
} node[MAX_N << 1];

int head[MAX_N];
int cnt;

void create(int u, int v);

int dep[MAX_N], siz[MAX_N];

template <typename T>
T read();

template <typename T>
void read(T& t);

template <typename T, typename... Args>
void read(T& t, Args&... rest);

int main() {
    std::ios::sync_with_stdio(false);

    auto segTree = std::make_unique<SegTree>();
    read(n, q);
    for (int i = 1; i < n; i++) {
        int x, y;
        read(x, y);
        create(x, y);
        create(y, x);
    }
    dep[1] = 1;

    segTree->dfs(1, 0);
    while (q--) {
        int x, y;
        read(x, y);
        std::cout << segTree->query(segTree->root[x], 1, n, dep[x] + 1,
                                    dep[x] + y) +
                         (ll)(siz[x] - 1) * std::min(dep[x] - 1, y)
                  << '\n';
    }

    return 0;
}

#define lc tree[x].l
#define rc tree[x].r

int SegTree::tree_merge(int a, int b) {
    if (!a or !b) {
        return a + b;
    }
    int r = ++cnt;
    tree[r].a = tree[a].a + tree[b].a;
    tree[r].l = tree_merge(tree[a].l, tree[b].l);
    tree[r].r = tree_merge(tree[a].r, tree[b].r);
    return r;
}

void SegTree::mod(int& x, int l, int r, const int& mk, const int& mv) {
    if (!x) {
        x = ++cnt;
    }
    tree[x].a += mv;
    if (l == r) {
        return;
    }
    const int mid = (l + r) >> 1;
    if (mk <= mid) {
        mod(lc, l, mid, mk, mv);
    } else {
        mod(rc, mid + 1, r, mk, mv);
    }
}

ll SegTree::query(int x, int l, int r, const int& ql, const int& qr) {
    if (!x) {
        return 0;
    }
    if (ql <= l and r <= qr) {
        return tree[x].a;
    }
    const int mid = (l + r) >> 1;
    ll res{};
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

void SegTree::dfs(int x, int f) {
    siz[x] = 1;
    for (int i = head[x]; i; i = node[i].nxt) {
        int v = node[i].v;
        if (v == f) {
            continue;
        }
        dep[v] = dep[x] + 1;
        dfs(v, x);
        siz[x] += siz[v];
    }
    mod(root[x], 1, n, dep[x], siz[x] - 1);
    if (f) {
        root[f] = tree_merge(root[f], root[x]);
    }
}

void create(int u, int v) {
    node[++cnt].v = v;
    node[cnt].nxt = head[u];
    head[u] = cnt;
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

template <typename T>
void read(T& t) {
    t = read<T>();
}

template <typename T, typename... Args>
void read(T& t, Args&... rest) {
    t = read<T>();
    read(rest...);
}