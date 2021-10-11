#include <cstdio>
#include <cstring>
#include <iostream>
#include <queue>

typedef long long ll;
typedef std::pair<ll, int> p;

const int MAX_N = 500050;

struct Node {
    int v;
    int nxt;
    int w;
} node[MAX_N];

int head[MAX_N];
ll dis[MAX_N];
bool ite[MAX_N], vis[MAX_N];
int cnt;
std::priority_queue<p, std::vector<p>, std::greater<p>> q;

void create(int u, int v, int w);

ll dij(int x);

template <typename T>
T read();

int main() {
    std::ios::sync_with_stdio(false);

    int t = read<int>();
    while (t--) {
        memset(head, 0, sizeof(head));
        memset(ite, 0, sizeof(ite));
        cnt = 0;

        int n = read<int>(), m = read<int>(), k = read<int>();
        for (int i = 1; i <= m; i++) {
            int x = read<int>(), y = read<int>(), z = read<int>();
            create(x, y, z);
        }

        for (int i = 1; i <= k; i++) {
            int x = read<int>();
            ite[x] = true;
        }

        ll ans = 4557430888798830399;
        for (int i = 1; i <= n; i++) {
            if (ite[i]) {
                ans = std::min(ans, dij(i));
            }
        }
        std::cout << ans << '\n';
    }

    return 0;
}

void create(int u, int v, int w) {
    node[++cnt].v = v;
    node[cnt].w = w;
    node[cnt].nxt = head[u];
    head[u] = cnt;
}

ll dij(int x) {
    while (!q.empty()) {
        q.pop();
    }
    memset(vis, 0, sizeof(vis));
    memset(dis, 0x3f, sizeof(dis));

    q.push(std::make_pair(0, x));
    dis[x] = 0;

    while (!q.empty()) {
        auto p = q.top();
        q.pop();
        auto u = p.second;

        if (ite[u] and u != x) {
            return dis[u];
        }
        if (!vis[u]) {
            vis[u] = true;
            for (int i = head[u]; i; i = node[i].nxt) {
                auto v = node[i].v, w = node[i].w;
                if (dis[v] > dis[u] + w) {
                    dis[v] = dis[u] + w;
                    q.push(std::make_pair(dis[v], v));
                }
            }
        }
    }

    return 4557430888798830399;
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