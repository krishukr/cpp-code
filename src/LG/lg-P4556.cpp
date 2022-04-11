#include <cstdio>
#include <iostream>
#include <memory>

constexpr int MAX_N = 100050;
constexpr int ML = 18;

struct Node {
    int v;
    int nxt;
} node[MAX_N << 2];

int cnt;
int head[MAX_N];

void create(int u, int v);

class SegTree {
   protected:
    struct Node {
        int a;
        int s;
        int lc;
        int rc;
    } tree[MAX_N << 6];

    int cnt;

    void seg_merge(const int& x);

   public:
    SegTree() = default;
    ~SegTree() = default;

    void mod(int& x, int l, int r, const int& mk, const int& mv);

    int tree_merge(int a, int b, int l, int r);

    const int query(const int& x) const { return tree[x].s ? tree[x].a : 0; }
};

std::unique_ptr<SegTree> segTree;

int fa[MAX_N][25];
int dep[MAX_N];

void dfs(int x, int f);

int lca(int a, int b);

int root[MAX_N], ans[MAX_N];

void solve(int x, int f);

template <typename T>
T read();

template <typename T>
void read(T& t);

template <typename T, typename... Args>
void read(T& t, Args&... rest);

int main() {
    std::ios::sync_with_stdio(false);

    int n, m;
    read(n, m);
    segTree = std::make_unique<SegTree>();

    for (int i = 1; i < n; i++) {
        int a, b;
        read(a, b);
        create(a, b);
        create(b, a);
    }
    dfs(1, 0);

    for (int i = 1; i <= m; i++) {
        int x, y, z;
        read(x, y, z);
        int l = lca(x, y);

        segTree->mod(root[x], 1, MAX_N - 50, z, 1);
        segTree->mod(root[y], 1, MAX_N - 50, z, 1);
        segTree->mod(root[l], 1, MAX_N - 50, z, -1);
        segTree->mod(root[fa[l][0]], 1, MAX_N - 50, z, -1);
    }
    solve(1, 0);

    for (int i = 1; i <= n; i++) {
        std::cout << ans[i] << '\n';
    }

    return 0;
}

void create(int u, int v) {
    node[++cnt].v = v;
    node[cnt].nxt = head[u];
    head[u] = cnt;
}

void SegTree::seg_merge(const int& x) {
    if (tree[x].lc == 0) {
        tree[x].s = tree[tree[x].rc].s;
        tree[x].a = tree[tree[x].rc].a;
        return;
    }
    if (tree[x].rc == 0) {
        tree[x].s = tree[tree[x].lc].s;
        tree[x].a = tree[tree[x].lc].a;
        return;
    }

    if (tree[tree[x].lc].s >= tree[tree[x].rc].s) {
        tree[x].s = tree[tree[x].lc].s;
        tree[x].a = tree[tree[x].lc].a;
    } else {
        tree[x].s = tree[tree[x].rc].s;
        tree[x].a = tree[tree[x].rc].a;
    }
}

void SegTree::mod(int& x, int l, int r, const int& mk, const int& mv) {
    if (x == 0) {
        x = ++cnt;
    }
    if (l == r) {
        tree[x].s += mv;
        tree[x].a = mk;
        return;
    }
    int mid = (l + r) >> 1;
    if (mk <= mid) {
        mod(tree[x].lc, l, mid, mk, mv);
    } else {
        mod(tree[x].rc, mid + 1, r, mk, mv);
    }
    seg_merge(x);
}

int SegTree::tree_merge(int a, int b, int l, int r) {
    if (!a or !b) {
        return a + b;
    }
    if (l == r) {
        tree[a].s += tree[b].s;
        return a;
    }
    int mid = (l + r) >> 1;
    tree[a].lc = tree_merge(tree[a].lc, tree[b].lc, l, mid);
    tree[a].rc = tree_merge(tree[a].rc, tree[b].rc, mid + 1, r);
    seg_merge(a);
    return a;
}

void dfs(int x, int f) {
    fa[x][0] = f;
    dep[x] = dep[f] + 1;
    for (int i = 1; i <= ML; i++) {
        fa[x][i] = fa[fa[x][i - 1]][i - 1];
    }

    for (int i = head[x]; i; i = node[i].nxt) {
        int v = node[i].v;
        if (v == f) {
            continue;
        }
        dfs(v, x);
    }
}

int lca(int a, int b) {
    if (dep[a] < dep[b]) {
        std::swap(a, b);
    }
    for (int i = ML; i >= 0; i--) {
        if (dep[fa[a][i]] >= dep[b]) {
            a = fa[a][i];
        }
    }
    if (a == b) {
        return a;
    }
    for (int i = ML; i >= 0; i--) {
        if (fa[a][i] != fa[b][i]) {
            a = fa[a][i];
            b = fa[b][i];
        }
    }
    return fa[a][0];
}

void solve(int x, int f) {
    for (int i = head[x]; i; i = node[i].nxt) {
        int v = node[i].v;
        if (v == f) {
            continue;
        }
        solve(v, x);
        root[x] = segTree->tree_merge(root[x], root[v], 1, MAX_N - 50);
    }
    ans[x] = segTree->query(root[x]);
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