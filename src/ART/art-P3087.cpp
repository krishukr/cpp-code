#include <cstdio>
#include <functional>
#include <iostream>
#include <memory>
#include <queue>
#include <vector>

template <typename T>
using pq = std::priority_queue<T, std::vector<T>, std::greater<T>>;

constexpr int MAX_N = 1000050;

class Solution {
    int dis[MAX_N];
    bool vis[MAX_N];

   public:
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
        auto solutuin = std::make_unique<Solution>();
        solutuin->solve();
    }

    std::cout << std::flush;
    return 0;
}

void Solution::solve() {
    std::fill(dis, dis + MAX_N, 114514);

    int n;
    read(n);

    pq<std::pair<int, int>> q;
    q.push({1, 1});
    dis[1] = 1;
    while (!q.empty()) {
        const auto p = q.top().second;
        q.pop();
        if (vis[p]) {
            continue;
        }
        vis[p] = true;

        for (int i = 0; i <= 1; i++) {
            const auto v = (2 * p + i) % n, w = i;
            if (dis[v] > dis[p] + w) {
                dis[v] = dis[p] + w;
                q.push({dis[v], v});
            }
        }
    }

    std::cout << dis[0] << '\n';
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