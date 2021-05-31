#include <cstring>
#include <iostream>

const int MAX_N = 20010;

struct Node {
    int u;
    int v;
} node[MAX_N << 1];

int head[MAX_N], dp[MAX_N];
bool vis[MAX_N];
int cnt, n, num, ans;

void create(int u, int v);

void dfs(int x);

int main() {
    std::ios::sync_with_stdio(false);

    int T;
    std::cin >> T;
    while (T--) {
        memset(head, -1, sizeof(head));
        memset(dp, 0, sizeof(dp));
        memset(vis, false, sizeof(vis));
        num = __INT_MAX__;
        ans = cnt = 0;

        int x;
        std::cin >> n;
        for (int i = 1; i < n; i++) {
            int u, v;
            std::cin >> u >> v;
            create(u, v);
            create(v, u);
            x = u;
        }
        dfs(x);
        std::cout << ans << ' ' << num << '\n';
    }

    return 0;
}

void create(int u, int v) {
    node[++cnt].u = v;
    node[cnt].v = head[u];
    head[u] = cnt;
}

void dfs(int x) {
    vis[x] = true;
    dp[x] = 0;
    int tmp = 0;
    for (int i = head[x]; i != -1; i = node[i].v) {
        if (!vis[node[i].u]) {
            dfs(node[i].u);
            dp[x] += dp[node[i].u] + 1;
            tmp = std::max(tmp, dp[node[i].u] + 1);
        }
    }
    tmp = std::max(tmp, n - dp[x] - 1);
    if (tmp < num or (tmp == num and x < ans)) {
        num = tmp;
        ans = x;
    }
}