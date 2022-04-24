#include <cstdio>
#include <iostream>

constexpr int MAX_N = 300050;
constexpr int INF = 0x3f3f3f3f;

int n, m;

struct Node {
    int v;
    int nxt;
} node[MAX_N << 1];

int head[MAX_N];
int cnt;

void create(int u, int v);

bool d[MAX_N];
int dp[MAX_N], g[MAX_N];
int ans;

void dfs(int x, int f, const int& p);

bool check(int x);

template <typename T>
T read();

template <typename T>
void read(T& t);

template <typename T, typename... Args>
void read(T& t, Args&... rest);

int main() {
    std::ios::sync_with_stdio(false);

    read(n, m);
    for (int i = 1; i <= n; i++) {
        d[i] = read<int>();
    }
    for (int i = 1; i < n; i++) {
        int x, y;
        read(x, y);
        create(x, y);
        create(y, x);
    }

    int l = 0, r = n, a;
    while (l <= r) {
        int mid = (l + r) >> 1;
        if (check(mid)) {
            r = mid - 1;
            a = mid;
        } else {
            l = mid + 1;
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

void dfs(int x, int f, const int& p) {
    dp[x] = -INF;
    g[x] = INF;
    for (int i = head[x]; i; i = node[i].nxt) {
        int v = node[i].v;
        if (v == f) {
            continue;
        }
        dfs(v, x, p);
        dp[x] = std::max(dp[x], dp[v] + 1);
        g[x] = std::min(g[x], g[v] + 1);
    }

    if (dp[x] + g[x] <= p) {
        dp[x] = -INF;
    }
    if (g[x] > p and d[x]) {
        dp[x] = std::max(dp[x], 0);
    }
    if (dp[x] == p) {
        dp[x] = -INF;
        g[x] = 0;
        ans++;
    }
}

bool check(int x) {
    ans = 0;
    dfs(1, 0, x);
    if (dp[1] >= 0) {
        ans++;
    }
    return ans <= m;
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