#include <cstdio>
#include <iomanip>
#include <iostream>

constexpr double EPS = 1e-8;
constexpr int MAX_N = 500050;

struct Node {
    int v;
    int nxt;
    int p;
} node[MAX_N << 1];

int head[MAX_N << 1];
int cnt;

void create(int u, int v, int p);

int q[MAX_N], dep[MAX_N];
double dp[MAX_N];
double ans;

void dfs1(int x);

void dfs2(int x);

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
        int a, b, p;
        read(a, b, p);
        create(a, b, p);
        create(b, a, p);
    }
    for (int i = 1; i <= n; i++) {
        read(q[i]);
        dp[i] = 0.01 * q[i];
    }

    dep[1] = 1;
    dfs1(1);
    dfs2(1);
    std::cout << std::fixed << std::setprecision(6) << ans << '\n';

    return 0;
}

void create(int u, int v, int p) {
    node[++cnt].v = v;
    node[cnt].nxt = head[u];
    node[cnt].p = p;
    head[u] = cnt;
}

void dfs1(int x) {
    for (int i = head[x]; i; i = node[i].nxt) {
        int v = node[i].v;
        double p = node[i].p;
        if (dep[v]) {
            continue;
        }
        dep[v] = dep[x] + 1;
        dfs1(v);
        const double k = dp[v] * p / 100;
        dp[x] = dp[x] + k - dp[x] * k;
    }
}

void dfs2(int x) {
    ans += dp[x];
    for (int i = head[x]; i; i = node[i].nxt) {
        int v = node[i].v;
        double p = node[i].p;
        if (dep[v] <= dep[x]) {
            continue;
        }
        if (std::abs((dp[v] * p / 100) - 1) <= EPS) {
            dfs2(v);
            continue;
        }
        const double k =
            (dp[x] - dp[v] * p / 100) / (1 - dp[v] * p / 100) * p / 100;
        dp[v] = dp[v] + k - dp[v] * k;
        dfs2(v);
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