#include <cstdio>
#include <cstring>
#include <iostream>
#include <queue>
#include <vector>

const int MAX_N = 100050;

int dp[MAX_N][55], dis[MAX_N];
bool vis[MAX_N], pa[MAX_N][55];
bool flag;

int n, m, k, p;

struct Node {
    int v;
    int w;
};

std::vector<Node> g1[MAX_N], g2[MAX_N];

void dp1();

int dp2(int u, int x);

template <typename T>
T read();

int main() {
    freopen("park.in", "r", stdin);
    freopen("park.out", "w", stdout);

    int T = read<int>();
    while (T--) {
        n = read<int>(), m = read<int>(), k = read<int>(), p = read<int>();

        for (int i = 1; i <= m; i++) {
            int u = read<int>(), v = read<int>(), w = read<int>();
            g1[u].push_back((Node){v, w});
            g2[v].push_back((Node){u, w});
        }
        dp1();

        dp2(1, 0);
        dp[1][0] = 1;
        int res = 0;
        for (int i = 0; i <= k; i++) {
            res += dp2(n, i);
            res %= p;
        }
        if (flag) {
            std::cout << "-1\n";
        } else {
            std::cout << res << '\n';
        }

        flag = false;
        memset(dp, 0, sizeof(dp));
        memset(pa, 0, sizeof(pa));
        for (int i = 1; i <= n; i++) {
            g1[i].clear();
            g2[i].clear();
        }
    }

    fclose(stdin);
    fclose(stdout);
    return 0;
}

void dp1() {
    memset(vis, 0, sizeof(vis));
    memset(dis, 0x3f, sizeof(dis));
    std::priority_queue<std::pair<int, int>> q;
    q.push(std::make_pair(0, 1));
    dis[1] = 0;

    while (!q.empty()) {
        int u = q.top().second;
        q.pop();
        if (vis[u]) {
            continue;
        } else {
            vis[u] = true;
            for (auto i : g1[u]) {
                int v = i.v, w = i.w;
                if (dis[u] + w < dis[v]) {
                    dis[v] = dis[u] + w;
                    q.push(std::make_pair(-dis[v], v));
                }
            }
        }
    }
}

int dp2(int u, int x) {
    if (x < 0) {
        return 0;
    }
    if (pa[u][x]) {
        flag = true;
        return 0;
    }
    if (dp[u][x]) {
        return dp[u][x];
    }

    pa[u][x] = true;
    int res = 0;

    for (auto i : g2[u]) {
        int v = i.v, w = i.w;
        res += dp2(v, dis[u] - dis[v] + x - w);
        res %= p;
        if (flag) {
            return 0;
        }
    }

    pa[u][x] = false;
    return (dp[u][x] = res);
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

// 91 pts
// 需要卡常