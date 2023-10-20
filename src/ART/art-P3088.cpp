#include <algorithm>
#include <cstdio>
#include <iostream>
#include <numeric>
#include <vector>

constexpr int MAX_N = 100050;

std::vector<int> G[MAX_N];
int deg[MAX_N], siz[MAX_N];

template <typename T>
T read();

template <typename T>
void read(T& t);

template <typename T, typename... Args>
void read(T& t, Args&... rest);

int main() {
    std::ios::sync_with_stdio(false);

    int n, m;
    read(n, m);
    for (int i = 1; i <= m; i++) {
        int x, y;
        read(x, y);
        G[x].push_back(y);
        G[y].push_back(x);
        deg[x]++;
        deg[y]++;
    }

    const auto cmp = [](const int& x, const int& y) -> bool {
        return deg[x] == deg[y] ? x < y : deg[x] < deg[y];
    };

    long long ans{};
    for (int u = 1; u <= n; u++) {
        for (const auto& v : G[u]) {
            if (!cmp(v, u)) {
                continue;
            }
            for (const auto& x : G[v]) {
                if (!cmp(x, u)) {
                    continue;
                }
                ans += siz[x];
                siz[x]++;
            }
        }
        for (const auto& v : G[u]) {
            if (!cmp(v, u)) {
                continue;
            }
            for (const auto& x : G[v]) {
                if (!cmp(x, u)) {
                    continue;
                }
                siz[x] = 0;
            }
        }
    }
    std::cout << ans << '\n';

    std::cout << std::flush;
    return 0;
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