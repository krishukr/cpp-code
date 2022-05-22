#include <cstdio>
#include <iostream>
#include <memory>

constexpr int MAX_N = 500050;
constexpr int MAX_L = 20;

struct Node {
    int v;
    int nxt;
} node[MAX_N << 1];

int head[MAX_N];
int cnt;

int fa[MAX_N];

void create(int u, int v);

void dfs(int x, int f);

int A[MAX_N], C[MAX_N];

class Trie {
   private:
    struct Node {
        int son[2];
        int a;
        int w;
        int d;
    } trie[MAX_N << 5];

    int cnt;

    int get_node(int d);

    void seg_merge(const int& x);

   public:
    int root[MAX_N];

    Trie() = default;
    Trie(const int& n) {
        for (int i = 1; i <= n; i++) {
            this->root[i] = (++cnt);
        }
    }
    ~Trie() = default;

    void mod(const int& x, const int& y);

    void add(const int& x);

    int query(const int x) const { return trie[root[x]].a; }
};

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
    for (int i = 1; i < n; i++) {
        int x, y;
        read(x, y);
        create(x, y);
        create(y, x);
    }
    dfs(1, 0);

    for (int i = 1; i <= n; i++) {
        read(A[i]);
    }
    auto trie = std::make_unique<Trie>(n);
    for (int i = 2; i <= n; i++) {
        trie->mod(trie->root[fa[i]], A[i]);
    }

    for (int i = 1; i <= m; i++) {
        int op;
        read(op);
        if (op == 1) {
            int x;
            read(x);
            C[x]++;
            trie->add(trie->root[x]);
            if (fa[x] == 0) {
                continue;
            }

            int u = fa[x], v = fa[fa[x]];
            if (v) {
                trie->mod(trie->root[v], A[u] + C[v]);
            }
            A[u]++;
            if (v) {
                trie->mod(trie->root[v], A[u] + C[v]);
            }
        } else if (op == 2) {
            int x, y;
            read(x, y);
            int u = x, v = fa[x];
            if (v) {
                trie->mod(trie->root[v], A[u] + C[v]);
            }
            A[u] -= y;
            if (v) {
                trie->mod(trie->root[v], A[u] + C[v]);
            }
        } else {
            int x;
            read(x);
            int u = fa[x], v = fa[fa[x]];
            if (!u) {
                std::cout << trie->query(x) << '\n';
            } else if (!v) {
                std::cout << (trie->query(x) ^ A[u]) << '\n';
            } else {
                std::cout << (trie->query(x) ^ (A[u] + C[v])) << '\n';
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

void dfs(int x, int f) {
    for (int i = head[x]; i; i = node[i].nxt) {
        int v = node[i].v;
        if (v == f) {
            continue;
        }
        fa[v] = x;
        dfs(v, x);
    }
}

#define lc trie[x].son[0]
#define rc trie[x].son[1]

int Trie::get_node(int d) {
    trie[++cnt] = {{0, 0}, 0, 0, d};
    return cnt;
}

void Trie::seg_merge(const int& x) {
    trie[x].w = trie[x].a = 0;
    if (lc) {
        trie[x].w ^= trie[lc].w;
        trie[x].a ^= (trie[lc].a << 1);
    }
    if (rc) {
        trie[x].w ^= trie[rc].w;
        trie[x].a ^= (trie[rc].a << 1);
        if (trie[rc].w == 1) {
            trie[x].a ^= 1;
        }
    }
}

void Trie::mod(const int& x, const int& y) {
    if (trie[x].d > MAX_L) {
        trie[x].w ^= 1;
        return;
    }
    if (y & (1 << trie[x].d)) {
        if (!rc) {
            rc = get_node(trie[x].d + 1);
        }
        mod(rc, y);
    } else {
        if (!lc) {
            lc = get_node(trie[x].d + 1);
        }
        mod(lc, y);
    }
    seg_merge(x);
}

void Trie::add(const int& x) {
    std::swap(lc, rc);
    if (lc) {
        add(lc);
    }
    seg_merge(x);
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

template <typename T>
void read(T& t) {
    t = read<T>();
}

template <typename T, typename... Args>
void read(T& t, Args&... rest) {
    t = read<T>();
    read(rest...);
}