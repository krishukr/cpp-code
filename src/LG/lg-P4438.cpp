#include <cstdio>
#include <cstring>
#include <iostream>

typedef long long ll;

const int MAX_N = 20050;
const int MAX_M = 45;

struct Que {
    ll x;
    ll y;
    ll v;
} q[MAX_N];

int son[MAX_N][MAX_M];
ll dp[MAX_N][MAX_M][MAX_M];
int n;

ll dfs(int x, int u, int v);

template <typename T>
T read();

int main() {
    std::ios::sync_with_stdio(false);

    n = read<int>();
    memset(dp, 0x3f, sizeof(dp));

    for (int i = 1; i < n; i++) {
        int x = read<int>(), y = read<int>();
        if (x < 0) {
            x = -x + n - 1;
        }
        if (y < 0) {
            y = -y + n - 1;
        }
        son[i][0] = x;
        son[i][1] = y;
    }

    for (int i = 1; i <= n; i++) {
        q[i].x = read<int>();
        q[i].y = read<int>();
        q[i].v = read<int>();
    }
    std::cout << dfs(1, 0, 0) << '\n';

    return 0;
}

ll dfs(int x, int u, int v) {
    if (x >= n) {
        return q[x - n + 1].v * (q[x - n + 1].x + u) * (q[x - n + 1].y + v);
    }
    if (dp[x][u][v] != dp[n + 1][41][41]) {
        return dp[x][u][v];
    }
    return dp[x][u][v] =
               std::min(dfs(son[x][0], u, v) + dfs(son[x][1], u, v + 1),
                        dfs(son[x][1], u, v) + dfs(son[x][0], u + 1, v));
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