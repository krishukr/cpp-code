#include <bits/stdc++.h>

#include <iomanip>
#include <memory>
#include <stack>

constexpr int MAX_N = 300050;

class Graph {
   public:
    Graph() = default;
    ~Graph() = default;

    struct {
        int v;
        int nxt;
    } node[MAX_N << 1];

    int head[MAX_N];
    int cnt;

    void create(int u, int v);

    int deg[MAX_N];
};

int x[MAX_N], y[MAX_N];
std::unique_ptr<Graph> g = nullptr;

int dfn[MAX_N], low[MAX_N], col[MAX_N], siz[MAX_N];
bool vis[MAX_N];
int idx, cot;
std::stack<int> stk;

void tarjan(int x);

int deg[MAX_N];
std::map<std::pair<int, int>, bool> usd;
int ans;

bool check(int x);

template <typename T>
T read();

template <typename T>
void read(T& t);

template <typename T, typename... Args>
void read(T& t, Args&... rest);

int main() {
    std::ios::sync_with_stdio(false);

    g = std::make_unique<Graph>();
    int n, m;
    read(n, m);
    for (int i = 1; i <= m; i++) {
        read(x[i], y[i]);
        g->create(x[i], y[i]);
    }
    for (int i = 1; i <= n; i++) {
        if (!dfn[i]) {
            tarjan(i);
        }
    }

    g = std::make_unique<Graph>();
    for (int i = 1; i <= m; i++) {
        const auto u = col[x[i]], v = col[y[i]];
        if (usd[{u, v}]) {
            continue;
        }
        usd[{u, v}] = true;
        if (u != v) {
            if (g->deg[v] == 0) {
                ans++;
            }
            g->deg[v]++;
            g->create(u, v);
        }
    }

    for (int i = 1; i <= cot; i++) {
        if (check(i)) {
            ans++;
            break;
        }
    }
    std::cout << std::fixed << std::setprecision(6)
              << (1.0 * (n - cot + ans) / n) << '\n';

    return 0;
}

void Graph::create(int u, int v) {
    node[++cnt].v = v;
    node[cnt].nxt = head[u];
    head[u] = cnt;
}

void tarjan(int x) {
    dfn[x] = low[x] = ++idx;
    vis[x] = true;
    stk.push(x);
    for (int i = g->head[x]; i; i = g->node[i].nxt) {
        const auto& v = g->node[i].v;
        if (!dfn[v]) {
            tarjan(v);
            low[x] = std::min(low[x], low[v]);
        } else if (vis[v]) {
            low[x] = std::min(low[x], dfn[v]);
        }
    }

    if (low[x] == dfn[x]) {
        int v;
        cot++;
        do {
            v = stk.top();
            stk.pop();
            vis[v] = false;
            col[v] = cot;
            siz[cot]++;
        } while (x != v);
    }
}

bool check(int x) {
    if (g->deg[x] or siz[x] > 1) {
        return false;
    }
    for (int i = g->head[x]; i; i = g->node[i].nxt) {
        const auto& v = g->node[i].v;
        if (g->deg[v] <= 1) {
            return false;
        }
    }
    return true;
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