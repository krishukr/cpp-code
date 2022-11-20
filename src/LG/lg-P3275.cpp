#include <cstdio>
#include <iostream>
#include <queue>
#include <stack>
#include <utility>
#include <vector>

using ll = long long;

constexpr int MAX_N = 100050;

struct {
    int v;
    int nxt;
    int w;
} node[MAX_N << 1];

int head[MAX_N];
int cnt;

void create(int u, int v, int w);

int dfn[MAX_N], low[MAX_N], col[MAX_N], siz[MAX_N];
bool vis[MAX_N];
std::stack<int> stk;
int idx, tot;

void tarjan(int x);

std::vector<std::pair<int, int>> nm[MAX_N];
int ind[MAX_N], f[MAX_N];

template <typename T>
T read();

template <typename T>
void read(T& t);

template <typename T, typename... Args>
void read(T& t, Args&... rest);

int main() {
    std::ios::sync_with_stdio(false);

    int n, k;
    read(n, k);
    for (int i = 1; i <= k; i++) {
        int x, a, b;
        read(x, a, b);
        if (x == 1) {
            create(a, b, 0);
            create(b, a, 0);
        } else if (x == 2) {
            create(a, b, 1);
        } else if (x == 3) {
            create(b, a, 0);
        } else if (x == 4) {
            create(b, a, 1);
        } else if (x == 5) {
            create(a, b, 0);
        }
    }

    for (int i = 1; i <= n; i++) {
        if (!dfn[i]) {
            tarjan(i);
        }
    }
    for (int x = 1; x <= n; x++) {
        for (int i = head[x]; i; i = node[i].nxt) {
            int v = node[i].v, w = node[i].w;
            const auto cv = col[v], cx = col[x];
            if (cx == cv and w == 1) {
                std::cout << -1 << '\n';
                return 0;
            }

            if (cx != cv) {
                nm[cx].push_back({cv, w});
                ind[cv]++;
            }
        }
    }

    std::queue<int> q;
    for (int i = 1; i <= tot; i++) {
        if (!ind[i]) {
            q.push(i);
            f[i] = 1;
        }
    }
    while (!q.empty()) {
        const auto p = q.front();
        q.pop();
        for (const auto& it : nm[p]) {
            const auto v = it.first, w = it.second;
            f[v] = std::max(f[v], f[p] + w);
            ind[v]--;
            if (!ind[v]) {
                q.push(v);
            }
        }
    }

    ll ans{};
    for (int i = 1; i <= tot; i++) {
        ans += 1ll * f[i] * siz[i];
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

void tarjan(int x) {
    dfn[x] = low[x] = ++idx;
    vis[x] = true;
    stk.push(x);
    for (int i = head[x]; i; i = node[i].nxt) {
        int v = node[i].v;
        if (!dfn[v]) {
            tarjan(v);
            low[x] = std::min(low[x], low[v]);
        } else if (vis[v]) {
            low[x] = std::min(low[x], dfn[v]);
        }
    }

    if (low[x] == dfn[x]) {
        int p;
        tot++;
        do {
            p = stk.top();
            stk.pop();
            vis[p] = false;
            col[p] = tot;
            siz[tot]++;
        } while (p != x);
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