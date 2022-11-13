#include <cstdio>
#include <iostream>
#include <memory>

constexpr int MAX_N = 50050;
constexpr int MAX_M = 1000050;

class Graph {
    struct {
        int v;
        int nxt;
    } node[MAX_M];

    int head[MAX_N];
    int cnt;

   public:
    Graph() = default;
    ~Graph() = default;

    void create(int u, int v);

    bool vis[MAX_N];

    void dfs(int x);
};

template <typename T>
T read();

template <typename T>
void read(T& t);

template <typename T, typename... Args>
void read(T& t, Args&... rest);

int main() {
    std::ios::sync_with_stdio(false);

    std::unique_ptr<Graph> G[6];
    for (int i = 0; i < 6; i++) {
        G[i] = std::make_unique<Graph>();
    }

    int n, k, m;
    read(n, k, m);
    for (int i = 1; i <= m; i++) {
        int x, y, z;
        read(x, y, z);
        z--;
        G[z * 2]->create(x, y);
        G[z * 2 + 1]->create(y, x);
    }

    for (int i = 0; i < k; i++) {
        G[i * 2]->dfs(1);
        G[i * 2 + 1]->dfs(1);
    }
    int a1{}, a2{};
    for (int i = 2; i <= n; i++) {
        int f1{1}, f2{1};
        for (int j = 0; j < k; j++) {
            if (!G[j * 2]->vis[i]) {
                f1 = 0;
            }
            if (!G[j * 2 + 1]->vis[i]) {
                f2 = 0;
            }
        }
        a1 += f1;
        a2 += f2;
    }
    std::cout << n - a1 << ' ' << a2 + 1 << '\n';

    return 0;
}

void Graph::create(int u, int v) {
    node[++cnt].v = v;
    node[cnt].nxt = head[u];
    head[u] = cnt;
}

void Graph::dfs(int x) {
    for (int i = head[x]; i; i = node[i].nxt) {
        const auto v = node[i].v;
        if (vis[v]) {
            continue;
        }
        vis[v] = true;
        dfs(v);
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