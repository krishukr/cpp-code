#include <iostream>

const int MAX_N = 105;

struct Node {
    int to;
    int nxt;
    int c;
} node[MAX_N << 1];

int dp[MAX_N][MAX_N], head[MAX_N];
int tot, n, q;

void create(int u, int v, int c);

void dfs(int x, int fa, int crt);

int main() {
    std::ios::sync_with_stdio(false);

    std::cin >> n >> q;
    for (int i = 1; i < n; i++) {
        int u, v, c;
        std::cin >> u >> v >> c;
        create(u, v, c);
        create(v, u, c);
    }

    dfs(1, 0, 0);
    std::cout << dp[1][q] << '\n';

    return 0;
}

void create(int u, int v, int c) {
    node[++tot].to = v;
    node[tot].nxt = head[u];
    node[tot].c = c;
    head[u] = tot;
}

void dfs(int x, int fa, int crt) {
    int son[MAX_N] = {0}, cnt = 0;
    bool flag = false;
    for (int i = head[x]; i; i = node[i].nxt) {
        if (node[i].to != fa) {
            flag = true;
            son[++cnt] = i;
            dfs(node[i].to, x, node[i].c);
        }
    }
    if (!flag) {
        return;
    }
    for (int i = 1; i <= q; i++) {
        for (int j = 0; j <= i; j++) {
            int tmp = 0;
            if (j - 1 >= 0) {
                tmp += node[son[1]].c;
            }
            if (i - j - 1 >= 0) {
                tmp += node[son[2]].c;
            }
            if (j != 0) {
                dp[x][i] =
                    std::max(dp[x][i], dp[node[son[1]].to][j - 1] + tmp +
                                           dp[node[son[2]].to][i - j - 1]);
            } else {
                dp[x][i] =
                    std::max(dp[x][i], dp[node[son[2]].to][i - j - 1] + tmp);
            }
        }
    }
}