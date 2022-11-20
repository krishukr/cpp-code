#include <cassert>
#include <cstdio>
#include <cstring>
#include <iostream>
#include <memory>

using ll = long long;

constexpr int MAX_N = 505;
constexpr ll INF = 1e12;

class Solution {
    struct {
        int v;
        int nxt;
        int w;
    } node[MAX_N << 1];

    int head[MAX_N];
    int cnt;

    void create(int u, int v, int w);

    bool S[MAX_N], T[MAX_N];
    ll f[MAX_N], g[MAX_N], s[MAX_N], d[MAX_N];

    void dfs(int x, int fa);

   public:
    Solution() = default;
    ~Solution() = default;

    void solve();
};

template <typename T>
T read();

template <typename T>
void read(T& t);

template <typename T, typename... Args>
void read(T& t, Args&... rest);

int main() {
    std::ios::sync_with_stdio(false);

    int T;
    read(T);
    while (T--) {
        auto solution = std::make_unique<Solution>();
        solution->solve();
    }

    return 0;
}

void Solution::create(int u, int v, int w) {
    node[++cnt].v = v;
    node[cnt].nxt = head[u];
    node[cnt].w = w;
    head[u] = cnt;
}

void Solution::dfs(int x, int fa) {
    g[x] = S[x] ? d[x] : INF;
    s[x] = T[x];
    for (int i = head[x]; i; i = node[i].nxt) {
        const auto v = node[i].v, w = node[i].w;
        if (v == fa) {
            continue;
        }
        d[v] = d[x] + w + 1;
        dfs(v, x);
        g[x] = std::min(g[x], g[v]);
        s[x] += s[v];
    }

    if (S[x]) {
        return;
    }
    if (T[x]) {
        f[x] = INF;
    } else {
        for (int i = head[x]; i; i = node[i].nxt) {
            const auto v = node[i].v, w = node[i].w;
            if (v == fa or s[v] == 0) {
                continue;
            }
            f[x] += std::max(0ll, std::min(f[v] - w - 1, g[v] - d[v] - w));
        }
    }
}

void Solution::solve() {
    int n, s, t;
    read(n, s, t);
    for (int i = 1; i < n; i++) {
        int x, y, z;
        read(x, y, z);
        create(x, y, z);
        create(y, x, z);
    }
    for (int i = 1; i <= s; i++) {
        int x;
        read(x);
        S[x] = true;
    }
    for (int i = 1; i <= t; i++) {
        int x;
        read(x);
        T[x] = true;
    }

    if (T[1]) {
        std::cout << "Impossible" << '\n';
        return;
    }
    dfs(1, 0);
    if (f[1] > 1e10) {
        std::cout << "Impossible" << '\n';
    } else {
        std::cout << f[1] << '\n';
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