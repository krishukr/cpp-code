#include <algorithm>
#include <cstdio>
#include <iostream>
#include <queue>

typedef long long ll;

const int MAX_N = 1000050;
const ll MOD = 2147483647;

struct Node {
    int v;
    int nxt;
    int w;
} node[MAX_N];

int cnt;
int head[MAX_N];

std::priority_queue<std::pair<int, int>, std::vector<std::pair<int, int>>,
                    std::greater<std::pair<int, int>>>
    q;
int dis[MAX_N], pat[MAX_N];
bool vis[MAX_N];

void create(int u, int v, int w);

void dij();

template <typename T>
T read();

int main() {
    std::ios::sync_with_stdio(false);

    int n = read<int>(), m = read<int>();
    for (int i = 1; i <= m; i++) {
        int x = read<int>(), y = read<int>(), z = read<int>();
        create(x, y, z);
        create(y, x, z);
    }

    std::fill(dis + 2, dis + n + 1, 0x3f3f3f3f);
    q.push(std::make_pair(0, 1));
    dij();

    ll ans = 1;
    for (int i = 2; i <= n; i++) {
        ans *= pat[i];
        ans %= MOD;
    }
    std::cout << ans << '\n';

    return 0;
}

void create(int u, int v, int w) {
    node[++cnt].v = v;
    node[cnt].nxt = head[u];
    node[cnt].w = w;
    head[u] = cnt;
}

void dij() {
    while (!q.empty()) {
        int p = q.top().second;
        q.pop();
        vis[p] = false;

        for (int i = head[p]; i; i = node[i].nxt) {
            int v = node[i].v, w = node[i].w;
            if (dis[v] > dis[p] + w) {
                pat[v] = 1;
                dis[v] = dis[p] + w;
                if (!vis[v]) {
                    q.push(std::make_pair(dis[v], v));
                    vis[v] = true;
                }
            } else if (dis[v] == dis[p] + w) {
                pat[v]++;
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
