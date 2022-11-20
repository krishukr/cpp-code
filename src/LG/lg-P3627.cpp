#include <algorithm>
#include <cstdio>
#include <iostream>
#include <memory>
#include <queue>
#include <stack>

constexpr int MAX_N = 500050;
constexpr int INF = 0x3f3f3f3f;

int dfn[MAX_N], low[MAX_N], col[MAX_N];
int tot;
std::stack<int> stk;

int a[MAX_N], b[MAX_N], p[MAX_N];
int dis[MAX_N];

class Graph {
    struct {
        int v;
        int nxt;
    } node[MAX_N << 1];

    int head[MAX_N];
    int cnt;

    bool vis[MAX_N];

   public:
    Graph() = default;
    ~Graph() = default;

    void create(int u, int v);

    void tarjan(int x);

    void spfa(int S);
};

int x[MAX_N], y[MAX_N];

template <typename T>
T read();

template <typename T>
void read(T& t);

template <typename T, typename... Args>
void read(T& t, Args&... rest);

int main() {
    std::ios::sync_with_stdio(false);

    int n, m, S, P;
    read(n, m);
    auto g = std::make_unique<Graph>();
    for (int i = 1; i <= m; i++) {
        read(x[i], y[i]);
        g->create(x[i], y[i]);
    }
    for (int i = 1; i <= n; i++) {
        read(b[i]);
        b[i] = -b[i];
    }
    read(S, P);
    for (int i = 1; i <= P; i++) {
        read(p[i]);
    }
    for (int i = 1; i <= n; i++) {
        if (!dfn[i]) {
            g->tarjan(i);
        }
    }

    g = std::make_unique<Graph>();
    for (int i = 1; i <= m; i++) {
        if (col[x[i]] == col[y[i]]) {
            continue;
        }
        g->create(col[x[i]], col[y[i]]);
    }
    g->spfa(col[S]);

    int res{INF};
    for (int i = 1; i <= P; i++) {
        res = std::min(res, dis[col[p[i]]]);
    }
    std::cout << -res << '\n';

    return 0;
}

void Graph::create(int u, int v) {
    node[++cnt].v = v;
    node[cnt].nxt = head[u];
    head[u] = cnt;
}

void Graph::tarjan(int x) {
    dfn[x] = low[x] = ++tot;
    stk.push(x);
    vis[x] = true;
    for (int i = head[x]; i; i = node[i].nxt) {
        const auto v = node[i].v;
        if (!dfn[v]) {
            tarjan(v);
            low[x] = std::min(low[x], low[v]);
        } else if (vis[v]) {
            low[x] = std::min(low[x], dfn[v]);
        }
    }
    if (dfn[x] == low[x]) {
        int p;
        tot++;
        do {
            p = stk.top();
            stk.pop();
            vis[p] = false;
            col[p] = tot;
            a[tot] += b[p];
        } while (p != x);
    }
}

void Graph::spfa(int S) {
    std::fill(dis, dis + tot + 10, INF);
    std::queue<int> q;
    q.push(S);
    dis[S] = a[S];
    while (!q.empty()) {
        const auto x = q.front();
        q.pop();
        vis[x] = false;
        for (int i = head[x]; i; i = node[i].nxt) {
            const auto v = node[i].v, w = a[v];
            if (dis[v] > dis[x] + w) {
                dis[v] = dis[x] + w;
                if (!vis[v]) {
                    q.push(v);
                    vis[v] = true;
                }
            }
        }
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