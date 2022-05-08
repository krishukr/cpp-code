#include <cstdio>
#include <iostream>
#include <memory>

constexpr int MAX_N = 100050;
constexpr int MAX_L = 30;

struct Node {
    int v;
    int nxt;
    int w;
} node[MAX_N << 1];

int head[MAX_N];
int cnt;

void create(int u, int v, int w);

int a[MAX_N];

void dfs(int x, int f);

class Trie {
   protected:
    struct Node {
        std::shared_ptr<Node> son[2]{nullptr, nullptr};
    };

   public:
    Trie() = default;
    ~Trie() = default;

    std::shared_ptr<Node> root = std::make_shared<Node>();

    void insert(int a);

    int query(int a);
};

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
    for (int i = 1; i < n; i++) {
        int u, v, w;
        read(u, v, w);
        create(u, v, w);
        create(v, u, w);
    }
    dfs(1, 0);

    auto trie = std::make_unique<Trie>();
    for (int i = 1; i <= n; i++) {
        trie->insert(a[i]);
    }

    int ans = 0;
    for (int i = 1; i <= n; i++) {
        ans = std::max(ans, trie->query(a[i]));
    }
    std::cout << ans << '\n';

    return 0;
}

void create(int u, int v, int w) {
    node[++cnt].v = v;
    node[cnt].nxt = head[u];
    node[cnt].w = w;
    head[u] = cnt;
}

void dfs(int x, int f) {
    for (int i = head[x]; i; i = node[i].nxt) {
        int v = node[i].v, w = node[i].w;
        if (v == f) {
            continue;
        }
        a[v] = a[x] ^ w;
        dfs(v, x);
    }
}

void Trie::insert(int a) {
    auto c = root;
    for (int i = MAX_L; i >= 0; i--) {
        const int x = (a >> i) & 1;
        c = (c->son[x] ? c->son[x] : (c->son[x] = std::make_shared<Node>()));
    }
}

int Trie::query(int a) {
    auto c = root;
    int ans{0};
    for (int i = MAX_L; i >= 0; i--) {
        const int x = (a >> i) & 1;
        if (c->son[x ^ 1]) {
            c = c->son[x ^ 1];
            ans = (ans << 1) | (x ^ 1);
        } else {
            c = c->son[x];
            ans = (ans << 1) | x;
        }
    }
    return ans ^ a;
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