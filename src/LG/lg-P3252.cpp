#include <cstdio>
#include <iostream>

constexpr int MAX_N = 100050;

struct {
    int v;
    int nxt;
} node[MAX_N];

int head[MAX_N];
int cnt;

void create(int u, int v);

int w[MAX_N];
int n, S, ans;

void dfs(int x, int d);

template <typename T>
T read();

template <typename T>
void read(T& t);

template <typename T, typename... Args>
void read(T& t, Args&... rest);

int main() {
    std::ios::sync_with_stdio(false);

    read(n, S);
    for (int i = 1; i <= n; i++) {
        read(w[i]);
    }
    for (int i = 1; i < n; i++) {
        int x, y;
        read(x, y);
        create(x, y);
    }
    for (int i = 1; i <= n; i++) {
        dfs(i, w[i]);
    }
    std::cout << ans << '\n';

    return 0;
}

void create(int u, int v) {
    node[++cnt].v = v;
    node[cnt].nxt = head[u];
    head[u] = cnt;
}

void dfs(int x, int d) {
    if (d > S) {
        return;
    }
    if (d == S) {
        ans++;
        return;
    }
    for (int i = head[x]; i; i = node[i].nxt) {
        const auto v = node[i].v;
        dfs(v, d + w[v]);
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