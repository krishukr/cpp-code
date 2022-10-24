#include <cstdio>
#include <iostream>
#include <memory>
#include <queue>

constexpr int MAX_N = 2000050;

class Solution {
    struct {
        int v;
        int nxt;
    } node[MAX_N << 1];

    int head[MAX_N];
    int cnt;

    void create(int u, int v);

    bool vis[MAX_N];
    int deg[MAX_N];

    bool check();

    int n, m;

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

void Solution::create(int u, int v) {
    node[++cnt].v = v;
    node[cnt].nxt = head[u];
    head[u] = cnt;
}

void Solution::solve() {
    read(n, m);
    for (int i = 1; i <= m; i++) {
        int x, y;
        read(x, y);
        deg[x]++;
        deg[n + y]++;
        create(x, n + y);
        create(n + y, x);
    }
    std::cout << (check() ? "Renko" : "Merry") << '\n';
}

bool Solution::check() {
    std::deque<int> q;
    for (int i = 1; i <= n * 2; i++) {
        if (deg[i] == 0) {
            return false;
        }
        if (deg[i] == 1) {
            vis[i] = true;
            q.push_back(i);
        }
    }

    int tot{};
    while (!q.empty()) {
        const auto p = q.front();
        q.pop_front();
        tot++;
        auto to{-1};
        for (int i = head[p]; i; i = node[i].nxt) {
            const auto v = node[i].v;
            if (vis[v]) {
                continue;
            }
            to = v;
        }
        if (to == -1) {
            continue;
        }

        vis[to] = true;
        tot++;
        for (int i = head[to]; i; i = node[i].nxt) {
            const auto v = node[i].v;
            if (vis[v]) {
                continue;
            }
            if (--deg[v] < 2) {
                q.push_back(v);
                vis[v] = true;
            }
        }
    }
    return tot >= n * 2;
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