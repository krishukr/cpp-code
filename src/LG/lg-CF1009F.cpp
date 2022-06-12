#include <cstdio>
#include <iostream>
#include <memory>

constexpr int MAX_N = 1000050;

class SegTree {
   private:
    struct Node {
        int l;
        int r;
        int k;
        int a;
    } tree[MAX_N * 24];

    int root[MAX_N];
    int cnt;

    void seg_merge(const int& x);

    void mod(int& x, int l, int r, const int& mk, const int& mv);

    int tree_merge(int a, int b, int l, int r);

    int n;
    int ans[MAX_N];

   public:
    SegTree() = default;
    SegTree(const int n) { this->n = n; }
    ~SegTree() = default;

    void dfs(int x, int f);

    void out() const {
        for (int i = 1; i <= n; i++) {
            std::cout << ans[i] << '\n';
        }
    }
};

struct Node {
    int v;
    int nxt;
} node[MAX_N << 1];

int head[MAX_N];
int cnt;

void create(int u, int v);

int dep[MAX_N];

void dfs(int x, int f);

template <typename T>
T read();

template <typename T>
void read(T& t);

template <typename T, typename... Args>
void read(T& t, Args&... rest);

int main() {
    std::ios::sync_with_stdio(false);

    int n;
    read(n);
    auto segTree = std::make_unique<SegTree>(n);
    for (int i = 1; i < n; i++) {
        int x, y;
        read(x, y);
        create(x, y);
        create(y, x);
    }

    dfs(1, 0);
    segTree->dfs(1, 0);
    segTree->out();

    return 0;
}

#define lc tree[x].l
#define rc tree[x].r

void SegTree::seg_merge(const int& x) {
    if (tree[lc].a < tree[rc].a or !lc) {
        tree[x].a = tree[rc].a;
        tree[x].k = tree[rc].k;
    } else {
        tree[x].a = tree[lc].a;
        tree[x].k = tree[lc].k;
    }
}

void SegTree::mod(int& x, int l, int r, const int& mk, const int& mv) {
    if (!x) {
        x = ++cnt;
    }
    if (l == r) {
        tree[x].a += mv;
        tree[x].k = mk;
        return;
    }
    const int mid = (l + r) >> 1;
    if (mk <= mid) {
        mod(lc, l, mid, mk, mv);
    } else {
        mod(rc, mid + 1, r, mk, mv);
    }
    seg_merge(x);
}

int SegTree::tree_merge(int a, int b, int l, int r) {
    if (!a or !b) {
        return a + b;
    }
    if (l == r) {
        tree[a].a += tree[b].a;
        tree[a].k = l;
        return a;
    }
    const int mid = (l + r) >> 1;
    tree[a].l = tree_merge(tree[a].l, tree[b].l, l, mid);
    tree[a].r = tree_merge(tree[a].r, tree[b].r, mid + 1, r);
    seg_merge(a);
    return a;
}

#undef lc
#undef rc

void create(int u, int v) {
    node[++cnt].v = v;
    node[cnt].nxt = head[u];
    head[u] = cnt;
}

void dfs(int x, int f) {
    dep[x] = dep[f] + 1;
    for (int i = head[x]; i; i = node[i].nxt) {
        int v = node[i].v;
        if (v == f) {
            continue;
        }
        dfs(v, x);
    }
}

void SegTree::dfs(int x, int f) {
    mod(root[x], 1, n, dep[x], 1);
    for (int i = head[x]; i; i = node[i].nxt) {
        int v = node[i].v;
        if (v == f) {
            continue;
        }
        dfs(v, x);
        root[x] = tree_merge(root[x], root[v], 1, n);
    }
    ans[x] = tree[root[x]].k - dep[x];
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