#include <algorithm>
#include <cstdio>
#include <iostream>
#include <memory>
#include <queue>

class Solution {
   private:
    constexpr static int MAX_N = 2050;

    struct {
        int v;
        int w;
        int nxt;
    } node[MAX_N << 2];

    int head[MAX_N];
    int cnt;

    void create(int u, int v, int w);

    bool vis[MAX_N];
    int dis[MAX_N], tot[MAX_N];

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
    const int S = 1;
    for (int i = 1; i <= m; i++) {
        int x, y, z;
        read(x, y, z);
        create(x, y, z);
        if (z >= 0) {
            create(y, x, z);
        }
    }
    std::fill(dis + 2, dis + n + 1, 0x3f3f3f3f);

    std::queue<int> q;
    q.push(S);
    vis[S] = true;
    tot[S]++;
    while (!q.empty()) {
        const auto p = q.front();
        q.pop();
        vis[p] = false;
        for (int i = head[p]; i; i = node[i].nxt) {
            const auto v = node[i].v, w = node[i].w;
            if (dis[v] > dis[p] + w) {
                dis[v] = dis[p] + w;
                if (!vis[v]) {
                    q.push(v);
                    vis[v] = true;
                    tot[v]++;
                    if (tot[v] > n) {
                        std::cout << "YES\n";
                        return;
                    }
                }
            }
        }
    }

    std::cout << "NO\n";
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
