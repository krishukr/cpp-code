#include <cstdio>
#include <iostream>

constexpr int MAX_N = 200050;
constexpr int MAX_L = 22;

struct {
    int v;
    int nxt;
} node[MAX_N];

int head[MAX_N];
int cnt;

void create(int u, int v);

int d[MAX_N];
int f[MAX_L][MAX_N];

void dfs(int x, int fa);

int LCA(int x, int y);

int op[MAX_N], x[MAX_N], y[MAX_N], c[MAX_N], t[MAX_N];

class HJT {
   protected:
    struct {
        int lc;
        int rc;
        int a;
    } tree[MAX_N << 5];

    int tot;

   public:
    int root[MAX_N];

    void build(int& x, int l, int r);

    void mod(int& x, int y, int l, int r, const int& mk);

    int query(int x, int y, int l, int r, int qk);
} hjt;

int n, S, q;

template <typename T>
T read();

template <typename T>
void read(T& t);

template <typename T, typename... Args>
void read(T& t, Args&... rest);

int main() {
    std::ios::sync_with_stdio(false);

    read(n);
    for (int i = 1; i <= n; i++) {
        int x;
        read(x);
        if (x) {
            create(x, i);
        } else {
            S = i;
        }
    }

    read(q);
    for (int i = 1; i <= n; i++) {
        t[i] = q;
    }
    for (int i = 1; i <= q; i++) {
        read(op[i]);
        if (op[i] == 1) {
            read(x[i], y[i], c[i]);
        } else {
            read(x[i]);
            t[x[i]] = i;
        }
    }

    hjt.build(hjt.root[0], 0, q);
    dfs(S, 0);
    for (int i = 1; i <= q; i++) {
        if (op[i] == 1) {
            const auto l = LCA(x[i], y[i]);
            std::cout << d[x[i]] + d[y[i]] - 2 * d[l] + 1 << ' ';
            if (i - c[i] < 1) {
                std::cout << 0 << '\n';
            } else {
                std::cout << hjt.query(hjt.root[x[i]], hjt.root[l], 0, q,
                                       i - c[i] - 1) +
                                 hjt.query(hjt.root[y[i]], hjt.root[f[0][l]], 0,
                                           q, i - c[i] - 1)
                          << '\n';
            }
        }
    }

    return 0;
}

void create(int u, int v) {
    node[++cnt].v = v;
    node[cnt].nxt = head[u];
    head[u] = cnt;
}

void dfs(int x, int fa) {
    hjt.mod(hjt.root[x], hjt.root[fa], 0, q, t[x]);
    d[x] = d[fa] + 1;
    for (int i = 0; i + 1 < MAX_L; i++) {
        f[i + 1][x] = f[i][f[i][x]];
    }
    for (int i = head[x]; i; i = node[i].nxt) {
        int v = node[i].v;
        if (v == fa) {
            continue;
        }
        f[0][v] = x;
        dfs(v, x);
    }
}

int LCA(int x, int y) {
    if (d[x] < d[y]) {
        std::swap(x, y);
    }
    if (d[x] != d[y]) {
        for (int i = MAX_L - 1; i >= 0; i--) {
            if (d[y] <= d[f[i][x]]) {
                x = f[i][x];
            }
        }
    }
    if (x == y) {
        return x;
    }
    for (int i = MAX_L - 1; i >= 0; i--) {
        if (f[i][x] == f[i][y]) {
            continue;
        }
        x = f[i][x];
        y = f[i][y];
    }
    return f[0][x];
}

void HJT::build(int& x, int l, int r) {
    x = ++tot;
    if (l == r) {
        return;
    }
    const auto mid = (l + r) >> 1;
    build(tree[x].lc, l, mid);
    build(tree[x].rc, mid + 1, r);
}

void HJT::mod(int& x, int y, int l, int r, const int& mk) {
    x = ++tot;
    tree[x] = tree[y];
    tree[x].a++;
    if (l == r) {
        return;
    }
    const auto mid = (l + r) >> 1;
    if (mk <= mid) {
        mod(tree[x].lc, tree[y].lc, l, mid, mk);
    } else {
        mod(tree[x].rc, tree[y].rc, mid + 1, r, mk);
    }
}

int HJT::query(int x, int y, int l, int r, int qk) {
    if (r <= qk) {
        return tree[x].a - tree[y].a;
    }
    if (tree[x].a - tree[y].a == 0) {
        return 0;
    }
    const auto mid = (l + r) >> 1;
    if (qk <= mid) {
        return query(tree[x].lc, tree[y].lc, l, mid, qk);
    } else {
        return tree[tree[x].lc].a - tree[tree[y].lc].a +
               query(tree[x].rc, tree[y].rc, mid + 1, r, qk);
    }
}

template <typename T>
T read() {
    T x = 0, f = 1;
    char ch = getchar_unlocked();
    while (!isdigit(ch)) {
        if (ch == '-') f = -1;
        ch = getchar_unlocked();
    }
    while (isdigit(ch)) {
        x = x * 10 + ch - 48;
        ch = getchar_unlocked();
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