#include <cstdio>
#include <cstring>
#include <iostream>
#include <queue>

typedef long long ll;

const int MAX_N = 105;

struct Node {
    int v;
    int nxt;
    int w;
} node[MAX_N];

int head[MAX_N];
int cnt;

ll dp[MAX_N], dis[MAX_N], cst[MAX_N][MAX_N];
bool block[MAX_N], vis[MAX_N], ban[MAX_N][MAX_N];
int n, m, k, e;

void create(int u, int v, int w);

void spfa();

template <typename T>
T read();

int main() {
    std::ios::sync_with_stdio(false);

    n = read<int>(), m = read<int>(), k = read<int>(), e = read<int>();

    for (int i = 1; i <= e; i++) {
        int x = read<int>(), y = read<int>(), z = read<int>();
        create(x, y, z);
        create(y, x, z);
    }

    int d = read<int>();
    for (int i = 1; i <= d; i++) {
        int p = read<int>(), a = read<int>(), b = read<int>();
        for (int j = a; j <= b; j++) {
            ban[p][j] = true;
        }
    }

    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= n; j++) {
            memset(block, 0, sizeof(block));
            for (int k = i; k <= j; k++) {
                for (int l = 1; l <= m; l++) {
                    if (ban[l][k]) {
                        block[l] = ban[l][k];
                    }
                }
            }

            spfa();
            cst[i][j] = dis[m];
        }
    }

    memset(dp, 0x3f, sizeof(dp));

    for (int i = 1; i <= n; i++) {
        dp[i] = cst[1][i] * i;
        for (int j = i - 1; j >= 0; j--) {
            dp[i] = std::min(dp[i], dp[j] + cst[j + 1][i] * (i - j) + k);
        }
    }
    std::cout << dp[n] << '\n';

    return 0;
}

void create(int u, int v, int w) {
    node[++cnt].v = v;
    node[cnt].w = w;
    node[cnt].nxt = head[u];
    head[u] = cnt;
}

void spfa() {
    for (int i = 0; i <= m; i++) {
        dis[i] = 0x3f3f3f3f;
        vis[i] = false;
    }
    std::queue<int> q;
    q.push(1);
    dis[1] = 0;

    while (!q.empty()) {
        int p = q.front();
        q.pop();
        vis[p] = false;

        for (int i = head[p]; i; i = node[i].nxt) {
            int v = node[i].v, w = node[i].w;
            if (block[v]) {
                continue;
            }

            if (dis[v] > dis[p] + w) {
                dis[v] = dis[p] + w;
                if (!vis[v]) {
                    q.push(v);
                    vis[v] = true;
                }
            }
        }
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