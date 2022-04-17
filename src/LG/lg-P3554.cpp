#include <cstdio>
#include <iostream>

constexpr int MAX_N = 300050;

struct Node {
    int v;
    int nxt;
} node[MAX_N << 1];

int head[MAX_N];
int cnt;

void create(int u, int v);

int dp[MAX_N], cs[MAX_N];

void dfs1(int x, int f);

void dfs2(int x, int f, const int& m);

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
    for (int i = 1; i < n; i++) {
        int x, y;
        read(x, y);
        create(x, y);
        create(y, x);
    }
    dfs1(1, 0);

    int l = 0, r = 500000, a;
    while (l <= r) {
        int mid = (l + r) >> 1;
        dfs2(1, 0, mid);
        if (dp[1] > 0) {
            l = mid + 1;
        } else {
            r = mid - 1;
            a = mid;
        }
    }
    std::cout << a << '\n';

    return 0;
}

void create(int u, int v) {
    node[++cnt].v = v;
    node[cnt].nxt = head[u];
    head[u] = cnt;
}

void dfs1(int x, int f) {
    for (int i = head[x]; i; i = node[i].nxt) {
        int v = node[i].v;
        if (v == f) {
            continue;
        }
        cs[x]++;
        dfs1(v, x);
    }
}

void dfs2(int x, int f, const int& m) {
    dp[x] = cs[x] - m;
    for (int i = head[x]; i; i = node[i].nxt) {
        int v = node[i].v;
        if (v == f) {
            continue;
        }
        dfs2(v, x, m);
        if (dp[v] > 0) {
            dp[x] += dp[v];
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