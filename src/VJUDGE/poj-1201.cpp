#include <climits>
#include <cstring>
#include <iostream>
#include <queue>

const int MAX_N = 50010;

struct Node {
    int v;
    int w;
    int nxt;
} node[MAX_N << 2];

int head[MAX_N], dis[MAX_N], tot;
bool vis[MAX_N];

void add(int u, int v, int c);

int main() {
    std::ios::sync_with_stdio(false);
    memset(head, -1, sizeof(head));

    int n, l = 0x3fffffff, r = -l;
    std::queue<int> q;
    std::cin >> n;
    for (int i = 0; i < n; i++) {
        int a, b, c;
        std::cin >> a >> b >> c;
        add(b + 1, a, -c);
        l = std::min(l, a);
        r = std::max(r, b + 1);
    }

    for (int i = l; i < r; i++) {
        add(i, i + 1, 1);
        add(i + 1, i, 0);
    }
    std::fill(dis, dis + r + 10, INT_MAX);
    dis[r] = 0;

    q.push(r);
    vis[r] = true;
    while (!q.empty()) {
        int v = q.front();
        q.pop();
        vis[v] = false;

        for (int i = head[v]; i != -1; i = node[i].nxt) {
            if (dis[v] + node[i].w < dis[node[i].v]) {
                dis[node[i].v] = dis[v] + node[i].w;
                if (!vis[node[i].v]) {
                    q.push(node[i].v);
                    vis[node[i].v] = true;
                }
            }
        }
    }

    std::cout << -dis[l] << '\n';

    return 0;
}

void add(int u, int v, int c) {
    node[tot].v = v;
    node[tot].w = c;
    node[tot].nxt = head[u];
    head[u] = tot++;
}