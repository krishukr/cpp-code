#include <cstdio>
#include <iostream>
#include <map>
#include <memory>
#include <random>

using ll = long long;
using ull = unsigned ll;

constexpr int MAX_N = 500050;

std::mt19937_64 mrand(998244353);

class Solution {
    struct {
        int v;
        int nxt;
        ull w;
    } node[MAX_N << 1];

    int head[MAX_N];
    int cnt;

    void create(int u, int v, ull w);

    ull dis[MAX_N];

    void dfs(int x, int f);

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

void Solution::create(int u, int v, ull w) {
    node[++cnt].v = v;
    node[cnt].nxt = head[u];
    node[cnt].w = w;
    head[u] = cnt;
}

void Solution::dfs(int x, int f) {
    for (int i = head[x]; i; i = node[i].nxt) {
        const auto& v = node[i].v;
        const auto& w = node[i].w;
        if (v == f) {
            continue;
        }
        dis[v] = dis[x] ^ w;
        dfs(v, x);
    }
}

void Solution::solve() {
    int n;
    read(n);
    std::map<int, ull> mp;
    for (int i = 1; i < n; i++) {
        int x, y, z;
        read(x, y, z);
        ull t;
        if (mp.find(z) == mp.end()) {
            t = mp[z] = mrand();
        } else {
            t = mp[z];
        }
        create(x, y, t);
        create(y, x, t);
    }

    dfs(1, 0);
    std::map<ull, int> ap;
    for (int i = 1; i <= n; i++) {
        ap[dis[i]]++;
    }

    auto ans = 1ll * n * (n - 1) / 2;
    for (const auto& i : ap) {
        ans -= 1ll * i.second * (i.second - 1) / 2;
    }
    std::cout << ans << '\n';
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