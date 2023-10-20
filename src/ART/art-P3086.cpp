#include <cstdio>
#include <iostream>

constexpr int MAX_N = 5050;
constexpr int MOD = 1e9 + 7;

struct {
    int u;
    int v;
} p[MAX_N];

void create(int u, int v);

int ind[MAX_N];
long long ans{};
int n, m;

void dfs(int x, bool s);

template <typename T>
T read();

template <typename T>
void read(T& t);

template <typename T, typename... Args>
void read(T& t, Args&... rest);

int main() {
    std::ios::sync_with_stdio(false);

    read(n, m);
    if (m == 0) {
        std::cout << 0 << std::endl;
        return 0;
    }
    for (int i = 1; i < n; i++) {
        read(p[i].u, p[i].v);
    }
    dfs(1, true);
    dfs(1, false);
    std::cout << ans / 2 % MOD << '\n';

    std::cout << std::flush;
    return 0;
}

void dfs(int x, bool s) {
    if (x >= n) {
        std::fill(ind, ind + n + 1, 0);
        int cnt{};
        for (int i = 1; i < n; i++) {
            ind[p[i].v]++;
        }
        for (int i = 1; i <= n; i++) {
            cnt += ind[i] == 0;
        }
        ans += cnt == m;
        return;
    }
    if (s) {
        std::swap(p[x].u, p[x].v);
    }
    dfs(x + 1, true);
    dfs(x + 1, false);
    if (s) {
        std::swap(p[x].u, p[x].v);
    }
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