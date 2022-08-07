#include <cstdio>
#include <iostream>
#include <memory>

constexpr int MAX_N = 100050;

struct {
    char op;
    int x;
    int y;
} que[MAX_N];

struct {
    int v;
    int nxt;
} node[MAX_N << 1];

int head[MAX_N];
int cnt;

void create(int u, int v);

int dfn[MAX_N], siz[MAX_N], fat[MAX_N];
int idx;

void dfs(int x, int f);

int dsf[MAX_N];

int find(int x);

class SegTree {
   protected:
    struct {
        int l;
        int r;
        int s;
    } tree[MAX_N << 4];

    int cnt;

    void seg_merge(const int& x);

   public:
    SegTree() = default;
    ~SegTree() = default;

    int root[MAX_N];

    void mod(int& x, int l, int r, const int& mk);

    int tree_merge(int a, int b, int l, int r);

    int query(int x, int l, int r, const int& ql, const int& qr);
};

template <typename T>
T read();

template <typename T>
void read(T& t);

template <typename T, typename... Args>
void read(T& t, Args&... rest);

int main() {
    std::ios::sync_with_stdio(false);

    int n, q;
    read(n, q);
    for (int i = 1; i <= n; i++) {
        dsf[i] = i;
    }

    for (int i = 1; i <= q; i++) {
        char op = getchar();
        while (op != 'A' and op != 'Q') {
            op = getchar();
        }
        int x, y;
        read(x, y);
        que[i] = {op, x, y};
        if (op == 'A') {
            create(x, y);
            create(y, x);
        }
    }
    for (int i = 1; i <= n; i++) {
        if (!dfn[i]) {
            dfs(i, 0);
        }
    }

    auto segTree = std::make_unique<SegTree>();
    for (int i = 1; i <= n; i++) {
        segTree->mod(segTree->root[i], 1, n, dfn[i]);
    }
    for (int i = 1; i <= q; i++) {
        const auto op = que[i].op;
        auto x = que[i].x, y = que[i].y;
        if (op == 'A') {
            const auto fx = find(x), fy = find(y);
            dsf[fx] = fy;
            segTree->tree_merge(segTree->root[fy], segTree->root[fx], 1, n);
        } else if (op == 'Q') {
            if (fat[y] == x) {
                std::swap(x, y);
            }
            const auto fx = find(x);
            std::cout << (1ll *
                          segTree->query(segTree->root[fx], 1, n, dfn[x],
                                         dfn[x] + siz[x] - 1) *
                          (segTree->query(segTree->root[fx], 1, n, 1,
                                          dfn[x] - 1) +
                           segTree->query(segTree->root[fx], 1, n,
                                          dfn[x] + siz[x], n)))
                      << '\n';
        }
    }

    return 0;
}

void create(int u, int v) {
    node[++cnt].v = v;
    node[cnt].nxt = head[u];
    head[u] = cnt;
}

void dfs(int x, int f) {
    fat[x] = f;
    siz[x] = 1;
    dfn[x] = ++idx;
    for (int i = head[x]; i; i = node[i].nxt) {
        const auto v = node[i].v;
        if (v == f) {
            continue;
        }
        dfs(v, x);
        siz[x] += siz[v];
    }
}

int find(int x) { return dsf[x] == x ? x : (dsf[x] = find(dsf[x])); }

void SegTree::mod(int& x, int l, int r, const int& mk) {
    if (!x) {
        x = ++cnt;
    }
    if (l == r) {
        tree[x].s++;
        return;
    }
    const auto mid = (l + r) >> 1;
    if (mk <= mid) {
        mod(tree[x].l, l, mid, mk);
    } else {
        mod(tree[x].r, mid + 1, r, mk);
    }
    seg_merge(x);
}

void SegTree::seg_merge(const int& x) {
    if (!tree[x].l) {
        tree[x].s = tree[tree[x].r].s;
        return;
    }
    if (!tree[x].r) {
        tree[x].s = tree[tree[x].l].s;
        return;
    }
    tree[x].s = tree[tree[x].l].s + tree[tree[x].r].s;
}

int SegTree::tree_merge(int a, int b, int l, int r) {
    if (!a or !b) {
        return a + b;
    }
    if (l == r) {
        tree[a].s += tree[b].s;
        return a;
    }
    const auto mid = (l + r) >> 1;
    tree[a].l = tree_merge(tree[a].l, tree[b].l, l, mid);
    tree[a].r = tree_merge(tree[a].r, tree[b].r, mid + 1, r);
    seg_merge(a);
    return a;
}

int SegTree::query(int x, int l, int r, const int& ql, const int& qr) {
    if (!x or ql > qr) {
        return 0;
    }
    if (ql <= l and r <= qr) {
        return tree[x].s;
    }
    const auto mid = (l + r) >> 1;
    int res{};
    if (ql <= mid) {
        res += query(tree[x].l, l, mid, ql, qr);
    }
    if (mid < qr) {
        res += query(tree[x].r, mid + 1, r, ql, qr);
    }
    return res;
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