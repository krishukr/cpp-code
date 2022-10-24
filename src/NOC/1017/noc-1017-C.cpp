#include <cstdio>
#include <iostream>
#include <set>
#include <vector>

constexpr int MAX_N = 300050;

std::set<int> G[MAX_N];
std::vector<std::pair<int, int>> ori;

int fa[MAX_N];

int find(int x) { return fa[x] == x ? x : (fa[x] = find(fa[x])); }

int p[MAX_N], cnt[MAX_N];
bool ans[MAX_N];
int tot;

void dfs(int x);

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
        fa[i] = i;
    }
    for (int i = 1; i < n; i++) {
        int x, y, z;
        read(x, y, z);
        if (z) {
            ori.push_back({x, y});
        } else {
            fa[find(x)] = find(y);
        }
    }
    for (const auto& i : ori) {
        const auto x = find(i.first);
        const auto y = find(i.second);
        G[x].insert(y);
        G[y].insert(x);
    }
    for (int i = 1; i <= n; i++) {
        read(p[i]);
    }
    for (int i = 1; i <= n; i++) {
        cnt[find(p[i])]++;
    }

    for (int i = n; i >= 1; i--) {
        ans[i] = (tot == 0);
        if (--cnt[find(p[i])] == 0) {
            tot++;
            dfs(find(p[i]));
        }
    }
    for (int i = 1; i <= n; i++) {
        std::cout << (int)(ans[i]);
    }
    std::cout << '\n';

    return 0;
}

void dfs(int x) {
    if (G[x].size() <= 2 and !cnt[x]) {
        std::vector<int> t;
        for (const auto& i : G[x]) {
            t.push_back(i);
            for (const auto& j : G[x]) {
                if (i == j) {
                    continue;
                }
                G[i].insert(j);
            }
        }
        G[x].clear();
        tot--;
        for (const auto& i : t) {
            G[i].erase(x);
            dfs(i);
        }
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