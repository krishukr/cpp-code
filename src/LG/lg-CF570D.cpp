#include <cstdio>
#include <iostream>
#include <memory>

constexpr int MAX_N = 500050;

class SegTree {
   private:
    struct Node {
        int l;
        int r;
        int a;
    } tree[MAX_N << 5];

    int cnt;

    void seg_merge(const int& x);

    int tree_merge(int a, int b, int l, int r);

    void mod(int& x, int l, int r, const int& mk, const int& mv);

    std::unique_ptr<char[]> S;
    int mx;

    void dfs(int x, int f);

   public:
    SegTree() = default;
    SegTree(const int mx, std::unique_ptr<char[]> S) {
        this->mx = mx;
        this->S = std::move(S);
        this->dfs(1, 0);
    }
    ~SegTree() = default;

    int root[MAX_N];

    int query(int x, int l, int r, const int& qk);
};

struct Node {
    int v;
    int nxt;
} node[MAX_N << 1];

int head[MAX_N];
int cnt;

void create(int u, int v);

int dep[MAX_N];
int mx;

void dfs(int x, int f);

template <typename T>
T read();

template <typename T>
void read(T& t);

template <typename T, typename... Args>
void read(T& t, Args&... rest);

char read_lower();

int main() {
    std::ios::sync_with_stdio(false);

    int n, m;
    read(n, m);
    for (int i = 2; i <= n; i++) {
        int x;
        read(x);
        create(x, i);
        create(i, x);
    }
    auto S = std::make_unique<char[]>(n + 10);
    for (int i = 1; i <= n; i++) {
        S[i] = read_lower();
    }

    ::dfs(1, 0);
    auto segTree = std::make_unique<SegTree>(mx, std::move(S));

    while (m--) {
        int x, y;
        read(x, y);
        if (y > mx) {
            std::cout << "Yes" << '\n';
            continue;
        }
        const auto R = segTree->query(segTree->root[x], 1, mx, y);
        const auto T = (R & (-R));
        std::cout << ((R == T) ? "Yes" : "No") << '\n';
    }

    return 0;
}

#define lc tree[x].l
#define rc tree[x].r

void SegTree::seg_merge(const int& x) { tree[x].a = tree[lc].a ^ tree[rc].a; }

int SegTree::tree_merge(int a, int b, int l, int r) {
    if (!a or !b) {
        return a + b;
    }
    int x = ++cnt;
    if (l == r) {
        tree[x].a = tree[a].a ^ tree[b].a;
        return x;
    }
    const auto mid = (l + r) >> 1;
    lc = tree_merge(tree[a].l, tree[b].l, l, mid);
    rc = tree_merge(tree[a].r, tree[b].r, mid + 1, r);
    seg_merge(x);
    return x;
}

void SegTree::mod(int& x, int l, int r, const int& mk, const int& mv) {
    if (!x) {
        x = ++cnt;
    }
    if (l == r) {
        tree[x].a ^= mv;
        return;
    }
    const auto mid = (l + r) >> 1;
    if (mk <= mid) {
        mod(lc, l, mid, mk, mv);
    } else {
        mod(rc, mid + 1, r, mk, mv);
    }
    seg_merge(x);
}

int SegTree::query(int x, int l, int r, const int& qk) {
    if (l == r) {
        return tree[x].a;
    }
    const auto mid = (l + r) >> 1;
    if (qk <= mid) {
        return query(lc, l, mid, qk);
    } else {
        return query(rc, mid + 1, r, qk);
    }
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
    mx = std::max(mx, dep[x]);
    for (int i = head[x]; i; i = node[i].nxt) {
        const auto v = node[i].v;
        if (v == f) {
            continue;
        }
        dfs(v, x);
    }
}

void SegTree::dfs(int x, int f) {
    for (int i = head[x]; i; i = node[i].nxt) {
        const auto v = node[i].v;
        if (v == f) {
            continue;
        }
        dfs(v, x);
        root[x] = tree_merge(root[x], root[v], 1, mx);
    }
    mod(root[x], 1, mx, dep[x], 1 << (S[x] - 'a'));
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

char read_lower() {
    char ch = getchar();
    while (!islower(ch)) {
        ch = getchar();
    }
    return ch;
}