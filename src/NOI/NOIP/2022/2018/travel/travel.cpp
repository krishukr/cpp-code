#include <algorithm>
#include <cstdio>
#include <iostream>
#include <vector>

constexpr int MAX_N = 5050;

std::vector<int> G[MAX_N];

std::vector<int> ans;
bool vis[MAX_N];

void dfs(int x, int f);

template <typename T>
T read();

template <typename T>
void read(T& t);

template <typename T, typename... Args>
void read(T& t, Args&... rest);

int main() {
    freopen("travel.in", "r", stdin);
    freopen("travel.out", "w", stdout);
    std::ios::sync_with_stdio(false);

    int n, m;
    read(n, m);
    for (int i = 1; i <= m; i++) {
        int x, y;
        read(x, y);
        G[x].push_back(y);
        G[y].push_back(x);
    }
    for (int i = 1; i <= n; i++) {
        std::sort(G[i].begin(), G[i].end());
    }

    ans.reserve(n);
    dfs(1, 0);
    for (const auto& i : ans) {
        std::cout << i << ' ';
    }
    std::cout << '\n';

    std::cout << std::flush;
    fclose(stdin);
    fclose(stdout);
    return 0;
}

void dfs(int x, int f) {
    ans.push_back(x);
    for (const auto& v : G[x]) {
        if (vis[v] or v == f) {
            continue;
        }
        vis[v] = true;
        dfs(v, x);
    }
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