#include <cstdio>
#include <iostream>
#include <stack>

constexpr int MAX_N = 505;

struct {
    int v;
    int nxt;
} node[MAX_N * MAX_N];

int head[MAX_N];
int cnt;

void create(int u, int v);

std::stack<int> stk;
int dfn[MAX_N], low[MAX_N], col[MAX_N];
bool vis[MAX_N];
int tot, idx;

void tarjan(int x);

int id[MAX_N], od[MAX_N];

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
    for (int i = 1; i <= n; i++) {
        int x;
        do {
            read(x);
            if (x) {
                create(i, x);
            }
        } while (x);
    }

    for (int i = 1; i <= n; i++) {
        if (!dfn[i]) {
            tarjan(i);
        }
    }

    for (int j = 1; j <= n; j++) {
        for (int i = head[j]; i; i = node[i].nxt) {
            const auto u = col[j], v = col[node[i].v];
            if (u != v) {
                od[u]++;
                id[v]++;
            }
        }
    }

    int a1{}, a2{};
    for (int i = 1; i <= tot; i++) {
        a1 += id[i] == 0;
        a2 += od[i] == 0;
    }
    std::cout << a1 << '\n' << (tot > 1 ? std::max(a1, a2) : 0) << '\n';

    std::cout << std::flush;
    return 0;
}

void create(int u, int v) {
    node[++cnt].v = v;
    node[cnt].nxt = head[u];
    head[u] = cnt;
}

void tarjan(int x) {
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
            i = stk.top();
            stk.pop();
            vis[i] = false;
        } while (i != x);
    }
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