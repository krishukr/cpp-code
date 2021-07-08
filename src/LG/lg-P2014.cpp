#include <iostream>

const int MAX_N = 1005;

struct Node {
    int v;
    int nxt;
} node[MAX_N];

int head[MAX_N], dp[MAX_N][MAX_N];
int tot, n, m;

void create(int u, int v);

void dfs(int crt);

int main() {
    std::ios::sync_with_stdio(false);

    std::cin >> n >> m;
    for (int i = 1; i <= n; i++) {
        int k;
        std::cin >> k >> dp[i][1];
        create(k, i);
    }

    dfs(0);
    std::cout << dp[0][m + 1];

    return 0;
}

void create(int u, int v) {
    node[++tot].nxt = head[u];
    node[tot].v = v;
    head[u] = tot;
}

void dfs(int crt) {
    for (int i = head[crt]; i; i = node[i].nxt) {
        dfs(node[i].v);
        for (int j = m + 1; j > 0; j--) {
            for (int k = 1; k < j; k++) {
                dp[crt][j] =
                    std::max(dp[crt][j], dp[node[i].v][k] + dp[crt][j - k]);
            }
        }
    }
}