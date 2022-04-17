#include <algorithm>
#include <cstdio>
#include <iostream>

constexpr int MAX_N = 500050;

struct Node {
    int v;
    int nxt;
} node[MAX_N << 1];

int head[MAX_N];
int cnt;

void create(const int& u, const int& v);

int c[MAX_N], dp[MAX_N];
int siz[MAX_N], tmp[MAX_N];

void dfs(int x, int f);

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
        read(c[i]);
    }

    for (int i = 1; i < n; i++) {
        int a, b;
        read(a, b);
        create(a, b);
        create(b, a);
    }

    dfs(1, 0);
    std::cout << std::max(dp[1], siz[1] + c[1]) << '\n';

    return 0;
}

void create(const int& u, const int& v) {
    node[++cnt].v = v;
    node[cnt].nxt = head[u];
    head[u] = cnt;
}

void dfs(int x, int f) {
    if (x != 1) {
        dp[x] = c[x];
    }
    for (int i = head[x]; i; i = node[i].nxt) {
        int v = node[i].v;
        if (v == f) {
            continue;
        }
        dfs(v, x);
    }

    int tot = 0;
    for (int i = head[x]; i; i = node[i].nxt) {
        int v = node[i].v;
        if (v == f) {
            continue;
        }
        tmp[++tot] = v;
    }
    std::sort(tmp + 1, tmp + tot + 1, [](const int& x, const int& y) {
        return siz[x] - dp[x] < siz[y] - dp[y];
    });
    for (int i = 1; i <= tot; i++) {
        dp[x] = std::max(dp[x], dp[tmp[i]] + siz[x] + 1);
        siz[x] += siz[tmp[i]] + 2;
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