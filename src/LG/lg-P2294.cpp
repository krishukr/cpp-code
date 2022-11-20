#include <cstdio>
#include <cstring>
#include <iostream>
#include <memory>
#include <queue>

constexpr int MAX_N = 1050;

class Solution {
    struct {
        int v;
        int nxt;
        int w;
    } node[MAX_N << 2];

    int head[MAX_N];
    int cnt;

    void create(int u, int v, int w);

    int dis[MAX_N], bfx[MAX_N];
    bool vis[MAX_N];

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

void Solution::solve() {
    int n, m;
    read(n, m);
    const auto s = n + 1;
    for (int i = 1; i <= m; i++) {
        int x, y, z;
        read(x, y, z);
        x--;
        create(x, y, z);
        create(y, x, -z);
    }
    for (int i = 0; i <= n; i++) {
        create(s, i, 0);
    }

    memset(dis, 0x3f, sizeof(dis));
    std::queue<int> q;
    q.push(s);
    dis[s] = 0;
    while (!q.empty()) {
        const auto p = q.front();
        q.pop();
        vis[p] = false;
        for (int i = head[p]; i; i = node[i].nxt) {
            const auto v = node[i].v, w = node[i].w;
            if (dis[v] > dis[p] + w) {
                dis[v] = dis[p] + w;
                bfx[v] = bfx[p] + 1;
                if (bfx[v] > n) {
                    std::cout << "false" << '\n';
                    return;
                }
                if (!vis[v]) {
                    q.push(v);
                    vis[v] = true;
                }
            }
        }
    }
    std::cout << "true" << '\n';
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