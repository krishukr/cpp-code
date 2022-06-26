#include <cstdio>
#include <iostream>

constexpr int MAX_N = 7050;

int k[2], s[2][MAX_N];
int cnt[2][MAX_N];
bool vis[2][MAX_N], ans[2][MAX_N];
int n;

void dfs(int x, int p);

template <typename T>
T read();

template <typename T>
void read(T& t);

template <typename T, typename... Args>
void read(T& t, Args&... rest);

int main() {
    std::ios::sync_with_stdio(false);

    read(n);
    for (int i = 0; i < 2; i++) {
        read(k[i]);
        for (int j = 1; j <= k[i]; j++) {
            read(s[i][j]);
        }
    }

    dfs(1, 0);
    dfs(1, 1);
    for (int i = 0; i < 2; i++) {
        for (int j = 2; j <= n; j++) {
            if (!vis[i][j]) {
                std::cout << "Loop" << ' ';
                continue;
            }
            std::cout << (ans[i][j] ? "Win" : "Lose") << ' ';
        }
        std::cout << '\n';
    }

    return 0;
}

void dfs(int x, int p) {
    if (vis[p][x]) {
        return;
    }
    vis[p][x] = true;
    const int t = p ^ 1;
    for (int i = 1; i <= k[t]; i++) {
        const int f = (x - s[t][i] + n - 1) % n + 1;
        if (f == 1) {
            continue;
        }
        if (!ans[p][x]) {
            ans[t][f] = true;
            dfs(f, t);
        } else if (++cnt[t][f] == k[t]) {
            ans[t][f] = false;
            dfs(f, t);
        }
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