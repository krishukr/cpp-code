#include <cstdio>
#include <iomanip>
#include <iostream>

constexpr int MAX_N = 2505;

struct Node {
    int v;
    int nxt;
} node[MAX_N];

int head[MAX_N];
int cnt;

void create(int u, int v);

double S[MAX_N], P[MAX_N];
double a[MAX_N];
double dp[MAX_N][MAX_N];
int siz[MAX_N];
int K, n;

void dfs(int x, int f);

bool check(double x);

template <typename T>
T read();

int main() {
    std::ios::sync_with_stdio(false);

    K = read<int>(), n = read<int>();
    for (int i = 1; i <= n; i++) {
        S[i] = read<int>(), P[i] = read<int>();
        int f = read<int>();
        create(f, i);
    }

    double l = 0, r = 1e4;
    while (r - l > 1e-4) {
        double mid = (l + r) / 2;
        if (check(mid)) {
            l = mid;
        } else {
            r = mid;
        }
    }
    std::cout << std::fixed << std::setprecision(3) << l << '\n';

    return 0;
}

void create(int u, int v) {
    node[++cnt].v = v;
    node[cnt].nxt = head[u];
    head[u] = cnt;
}

void dfs(int x, int f) {
    dp[x][1] = a[x];
    siz[x] = 1;

    for (int i = head[x]; i; i = node[i].nxt) {
        int v = node[i].v;
        if (v == f) {
            continue;
        }
        dfs(v, x);
        siz[x] += siz[v];
        for (int j = std::min(siz[x], K + 1); j >= 1; j--) {
            for (int k = 0; k <= std::min(siz[v], j - 1); k++) {
                dp[x][j] = std::max(dp[x][j], dp[x][j - k] + dp[v][k]);
            }
        }
    }
}

bool check(double x) {
    a[0] = 0;
    for (int i = 1; i <= n; i++) {
        a[i] = P[i] - x * S[i];
    }
    for (int i = 0; i <= n; i++) {
        for (int j = 1; j <= K + 1; j++) {
            dp[i][j] = -1e10;
        }
    }
    dfs(0, -1);
    return dp[0][K + 1] >= 0;
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