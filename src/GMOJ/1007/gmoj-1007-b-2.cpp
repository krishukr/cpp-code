#include <climits>
#include <cstdio>
#include <iostream>

typedef long long ll;

const int MAX_N = 150;

bool vis[MAX_N][MAX_N];
ll dp[MAX_N][MAX_N], w[MAX_N], l[MAX_N], r[MAX_N];

ll dfs(int x, int y);

template <typename T>
T read();

int main() {
    std::ios::sync_with_stdio(false);

    int n = read<int>(), k = read<int>();

    for (int i = 2; i <= n; i++) {
        w[i] = read<ll>();
    }
    for (int i = 1; i <= n; i++) {
        l[i] = read<ll>();
        r[i] = read<ll>();
    }

    std::cout << dfs(1, k + 1);

    return 0;
}

ll dfs(int x, int y) {
    if (vis[x][y]) {
        return dp[x][y];
    }

    if (!x) {
        dp[x][y] = INT_MIN;
    } else if (!y) {
        dp[x][y] = 0;
    } else if (y == 1) {
        dp[x][y] = w[x];
    } else {
        ll res = INT_MIN;

        for (int i = 0; i < y; i++) {
            res = std::max(res, w[x] + dfs(l[x], i) + dfs(r[x], y - i - 1));
        }
        vis[x][y] = true;
        dp[x][y] = res;
    }
    return dp[x][y];
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