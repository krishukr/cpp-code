#include <cstdio>
#include <iostream>
#include <memory>

using ll = long long;

constexpr int MAX_N = 200050;

class SegTree {
   private:
    struct Node {
        int l;
        int r;
        ll s;
        ll a;
    } tree[MAX_N << 5];

    int cnt;

    void seg_merge(const int& x);

   public:
    SegTree(const int n) { this->cnt = n; }
    ~SegTree() = default;

    int tree_merge(int a, int b, ll l, ll r);

    void mod(int& x, ll l, ll r, const ll& mk);

    ll query(const int x) const { return tree[x].a; }
};

std::unique_ptr<SegTree> segTree = nullptr;
int n;
int C[MAX_N];

struct Node {
    int v;
    int nxt;
} node[MAX_N << 1];

int head[MAX_N];
int cnt;

void create(int u, int v);

int root[MAX_N];
ll res[MAX_N];

void dfs(int x, int f);

template <typename T>
T read();

template <typename T>
void read(T& t);

template <typename T, typename... Args>
void read(T& t, Args&... rest);

int main() {
    std::ios::sync_with_stdio(false);

    read(n);
    segTree = std::make_unique<SegTree>(n);
    for (int i = 1; i <= n; i++) {
        root[i] = i;
        segTree->mod(root[i], 1, n, read<int>());
    }

    for (int i = 1; i < n; i++) {
        int x, y;
        read(x, y);
        create(x, y);
        create(y, x);
    }
    dfs(1, 0);

    for (int i = 1; i <= n; i++) {
        std::cout << res[i] << ' ';
    }
    std::cout << '\n';

    return 0;
}

#define lc tree[x].l
#define rc tree[x].r

void SegTree::seg_merge(const int& x) {
    if (lc == 0 or tree[lc].s < tree[rc].s) {
        tree[x].a = tree[rc].a;
        tree[x].s = tree[rc].s;
        return;
    }
    if (rc == 0 or tree[lc].s > tree[rc].s) {
        tree[x].a = tree[lc].a;
        tree[x].s = tree[lc].s;
        return;
    }
    if (tree[lc].s == tree[rc].s) {
        tree[x].s = tree[lc].s;
        tree[x].a = tree[lc].a + tree[rc].a;
        return;
    }
}

int SegTree::tree_merge(int a, int b, ll l, ll r) {
    if (!a or !b) {
        return a + b;
    }
    if (l == r) {
        tree[a].s += tree[b].s;
        tree[a].a = l;
        return a;
    }
    const ll mid = (l + r) >> 1;
    tree[a].l = tree_merge(tree[a].l, tree[b].l, l, mid);
    tree[a].r = tree_merge(tree[a].r, tree[b].r, mid + 1, r);
    seg_merge(a);
    return a;
}

void SegTree::mod(int& x, ll l, ll r, const ll& mk) {
    if (!x) {
        x = ++cnt;
    }
    if (l == r) {
        tree[x].s++;
        tree[x].a = l;
        return;
    }
    const ll mid = (l + r) >> 1;
    if (mk <= mid) {
        mod(lc, l, mid, mk);
    } else {
        mod(rc, mid + 1, r, mk);
    }
    seg_merge(x);
}

#undef lc
#undef rc

void create(int u, int v) {
    node[++cnt].v = v;
    node[cnt].nxt = head[u];
    head[u] = cnt;
}

void dfs(int x, int f) {
    for (int i = head[x]; i; i = node[i].nxt) {
        int v = node[i].v;
        if (v == f) {
            continue;
        }
        dfs(v, x);
        root[x] = segTree->tree_merge(root[x], root[v], 1, n);
    }
    res[root[x]] = segTree->query(root[x]);
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