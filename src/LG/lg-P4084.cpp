#include <cstdio>
#include <iostream>

typedef long long ll;

const int MAX_N = 1000050;
const ll MOD = 1e9 + 7;

struct Node {
    int v;
    int nxt;
} node[MAX_N];

int head[MAX_N];
int cnt;

ll dp[5][MAX_N];

void create(int u, int v);

void dfs(int x, int f);

template <typename T>
T read();

int main() {
    std::ios::sync_with_stdio(false);

    int n = read<int>(), k = read<int>();

    for (int i = 1; i < n; i++) {
        int x = read<int>(), y = read<int>();
        create(x, y);
        create(y, x);
    }

    for (int i = 1; i <= k; i++) {
        int x = read<int>(), y = read<int>();
        dp[y][x] = 1;
    }

    dfs(1, 0);
    std::cout << (dp[1][1] + dp[2][1] + dp[3][1]) % MOD << '\n';

    return 0;
}

void create(int u, int v) {
    node[++cnt].v = v;
    node[cnt].nxt = head[u];
    head[u] = cnt;
}

void dfs(int x, int f) {
    for (int i = 1; i <= 3; i++) {
        if (dp[i][x]) {
            for (int j = 1; j < i; j++) {
                dp[j][x] = 0;
            }
            break;
        }
        dp[i][x] = 1;
    }

    for (int i = head[x]; i; i = node[i].nxt) {
        int v = node[i].v;
        if (v == f) {
            continue;
        }

        dfs(v, x);
        dp[1][x] = dp[1][x] * (dp[2][v] + dp[3][v] % MOD) % MOD;
        dp[2][x] = dp[2][x] * (dp[1][v] + dp[3][v] % MOD) % MOD;
        dp[3][x] = dp[3][x] * (dp[1][v] + dp[2][v] % MOD) % MOD;
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