#include <algorithm>
#include <cmath>
#include <cstdio>
#include <iostream>

const int MAX_N = 500050;
const float EPS = 5 * 1e-4;

struct Node {
    int v;
    int nxt;
} node[MAX_N << 1];

int head[MAX_N];
int cnt;

int v[MAX_N], ind[MAX_N];
float dp[MAX_N];

void create(int u, int v);

void dfs(int x, int f, float s);

template <typename T>
T read();

int main() {
    std::ios::sync_with_stdio(false);

    int n = read<int>();
    for (int i = 1; i <= n; i++) {
        v[i] = read<int>();
    }

    for (int i = 1; i < n; i++) {
        int x = read<int>(), y = read<int>();
        create(x, y);
        create(y, x);
        ind[x]++;
    }

    dfs(1, 0, 0);
    std::sort(dp + 1, dp + n + 1);

    int res = 1, ans = 0;
    for (int i = 2; i <= n; i++) {
        if (std::abs(dp[i] - dp[i - 1]) <= EPS) {
            res++;
            ans = std::max(ans, res);
        } else {
            res = 1;
        }
    }

    std::cout << n - ans << '\n';

    return 0;
}

void create(int u, int v) {
    node[++cnt].v = v;
    node[cnt].nxt = head[u];
    head[u] = cnt;
}

void dfs(int x, int f, float s) {
    dp[x] = s + std::log((float)(v[x]));
    for (int i = head[x]; i; i = node[i].nxt) {
        int v = node[i].v;
        if (v == f) {
            continue;
        }
        dfs(v, x, s + std::log((float)(ind[x])));
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