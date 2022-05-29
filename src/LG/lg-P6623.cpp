#include <cstdio>
#include <iostream>
#include <memory>

using ll = long long;

constexpr int MAX_N = 525050;

class Trie {
   private:
    struct Node {
        int son[2];
        bool v;
        int c;
        int w;
    } trie[MAX_N << 5];

    void seg_merge(const int& x);

   public:
    Trie() = default;
    ~Trie() = default;

    int root[MAX_N];
    int cnt;

    void insert(int& x, int y);

    int tree_merge(int x, int y);

    void add(int x);

    int query(const int& x) const { return trie[root[x]].w; }
};

struct Node {
    int v;
    int nxt;
} node[MAX_N];

int cnt;
int head[MAX_N];

void create(int u, int v);

int v[MAX_N];
std::unique_ptr<Trie> trie;
ll ans;

void dfs(int x);

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
    trie = std::make_unique<Trie>();
    for (int i = 1; i <= n; i++) {
        read(v[i]);
    }
    for (int i = 2; i <= n; i++) {
        create(read<int>(), i);
    }

    dfs(1);
    std::cout << ans << '\n';

    return 0;
}

#define lc trie[x].son[0]
#define rc trie[x].son[1]

void Trie::seg_merge(const int& x) {
    trie[x].c = trie[lc].c ^ trie[rc].c ^ trie[x].v;
    trie[x].w = (trie[lc].w << 1) ^ ((trie[rc].w << 1) | trie[rc].c);
}

void Trie::insert(int& x, int y) {
    if (!x) {
        x = ++cnt;
    }
    if (!y) {
        trie[x].v ^= 1;
        trie[x].c ^= 1;
        return;
    }
    insert(trie[x].son[y & 1], y >> 1);
    seg_merge(x);
}

void Trie::add(int x) {
    if (!x) {
        return;
    }
    std::swap(lc, rc);
    if (trie[x].v and !rc) {
        rc = ++cnt;
    }
    trie[rc].v ^= trie[x].v;
    trie[rc].c ^= trie[x].v;
    trie[x].v = false;
    add(lc);
    seg_merge(x);
}

int Trie::tree_merge(int x, int y) {
    if (!x or !y) {
        return x + y;
    }
    trie[x].v ^= trie[y].v;
    trie[x].c ^= trie[y].c;
    trie[x].w ^= trie[y].w;
    lc = tree_merge(lc, trie[y].son[0]);
    rc = tree_merge(rc, trie[y].son[1]);
    return x;
}

#undef lc
#undef rc

void create(int u, int v) {
    node[++cnt].v = v;
    node[cnt].nxt = head[u];
    head[u] = cnt;
}

void dfs(int x) {
    trie->insert(trie->root[x], v[x]);
    for (int i = head[x]; i; i = node[i].nxt) {
        int v = node[i].v;
        dfs(v);
        trie->add(trie->root[v]);
        trie->root[x] = trie->tree_merge(trie->root[x], trie->root[v]);
    }
    ans += trie->query(x);
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