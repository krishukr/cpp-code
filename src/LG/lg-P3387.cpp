#include <cstdio>
#include <iostream>
#include <memory>
#include <stack>

constexpr int MAX_N = 10050;
constexpr int MAX_M = 100050;

int w[MAX_N], cw[MAX_N];

class Solution {
    struct {
        int v;
        int nxt;
    } node[MAX_M];

    int head[MAX_N];
    int cnt;

    int f[MAX_N];

    int dfs(int x);

   public:
    int n;

    void create(int u, int v);

    int solve();
};

class Tarjan {
    struct {
        int v;
        int nxt;
    } node[MAX_M];

    int head[MAX_N];
    int cnt;

    std::stack<int> stk;
    int dfn[MAX_N], low[MAX_N], col[MAX_N];
    bool vis[MAX_N];
    int tot, idx;

   public:
    void create(int u, int v);

    void tarjan(int x);

    auto rebuild(int n, std::unique_ptr<Solution> s)
        -> std::unique_ptr<Solution>;
};

template <typename T>
T read();

template <typename T>
void read(T& t);

template <typename T, typename... Args>
void read(T& t, Args&... rest);

int main() {
    std::ios::sync_with_stdio(false);

    auto tarjan = std::make_unique<Tarjan>();
    int n, m;
    read(n, m);
    for (int i = 1; i <= n; i++) {
        read(w[i]);
    }
    for (int i = 1; i <= m; i++) {
        int x, y;
        read(x, y);
        tarjan->create(x, y);
    }

    std::cout << tarjan->rebuild(n, std::make_unique<Solution>())->solve()
              << '\n';

    std::cout << std::flush;
    return 0;
}

void Solution::create(int u, int v) {
    node[++cnt].v = v;
    node[cnt].nxt = head[u];
    head[u] = cnt;
}
void Tarjan::create(int u, int v) {
    node[++cnt].v = v;
    node[cnt].nxt = head[u];
    head[u] = cnt;
}

int Solution::dfs(int x) {
    if (f[x]) {
        return f[x];
    }
    f[x] = cw[x];

    int res{};
    for (int i = head[x]; i; i = node[i].nxt) {
        const auto& v = node[i].v;
        res = std::max(res, dfs(v));
    }
    return f[x] += res;
}

int Solution::solve() {
    int res{};
    for (int i = 1; i <= n; i++) {
        res = std::max(res, dfs(i));
    }
    return res;
}

void Tarjan::tarjan(int x) {
    dfn[x] = low[x] = ++idx;
    stk.push(x);
    vis[x] = true;

    for (int i = head[x]; i; i = node[i].nxt) {
        const auto& v = node[i].v;
        if (!dfn[v]) {
            tarjan(v);
            low[x] = std::min(low[x], low[v]);
        } else if (vis[v]) {
            low[x] = std::min(low[x], dfn[v]);
        }
    }

    if (dfn[x] == low[x]) {
        ++tot;
        int i = x;
        do {
            col[i] = tot;
            cw[tot] += w[i];
            i = stk.top();
            stk.pop();
            vis[i] = false;
        } while (i != x);
    }
}

auto Tarjan::rebuild(int n, std::unique_ptr<Solution> s)
    -> std::unique_ptr<Solution> {
    for (int i = 1; i <= n; i++) {
        if (!dfn[i]) {
            tarjan(i);
        }
    }

    s->n = tot;
    for (int j = 1; j <= n; j++) {
        for (int i = head[j]; i; i = node[i].nxt) {
            const auto& v = node[i].v;
            if (col[j] != col[v]) {
                s->create(col[j], col[v]);
            }
        }
    }
    return std::move(s);
}

template <typename T>
T read() {
    T x{}, f{1};
    int ch = getchar_unlocked();
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