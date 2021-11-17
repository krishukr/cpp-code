#include <algorithm>
#include <cstdio>
#include <iostream>
#include <queue>

const int MAX_N = 10000050;

struct Node {
    int v;
    int nxt;
    int w;
} node[MAX_N];

int head[MAX_N];
int cnt;

int dis[MAX_N];

std::priority_queue<std::pair<int, int>, std::vector<std::pair<int, int>>,
                    std::greater<std::pair<int, int>>>
    q;

void create(int u, int v, int w);

template <typename T>
T read();

int main() {
    std::ios::sync_with_stdio(false);

    int n = read<int>(), m = read<int>();
    int s = 2 * n * m + 5, t = 2 * n * m + 6;

    for (int i = 1; i < m; i++) {
        int x = read<int>();
        create(i + i, t, x);
    }

    for (int i = 2; i < n; i++) {
        for (int j = 1; j < m; j++) {
            int x = 2 * (i - 2) * (m - 1) - 1 + 2 * j;
            int y = 2 * (i - 1) * (m - 1) + 2 * j;
            int z = read<int>();
            create(x, y, z);
            create(y, x, z);
        }
    }

    for (int i = 1; i < m; i++) {
        int x = 2 * (n - 2) * (m - 1) - 1 + 2 * i;
        int y = read<int>();
        create(s, x, y);
    }

    for (int i = 1; i < n; i++) {
        for (int j = 1; j <= m; j++) {
            int x = 2 * (i - 1) * (m - 1) - 1 + 2 * j;
            int y = 2 * (i - 1) * (m - 1) - 2 + 2 * j;
            int z = read<int>();
            if (j == 1) {
                create(s, x, z);
            } else if (j == m) {
                create(y, t, z);
            } else {
                create(x, y, z);
                create(y, x, z);
            }
        }
    }

    for (int i = 1; i < n; i++) {
        for (int j = 1; j < m; j++) {
            int x = 2 * (i - 1) * (m - 1) - 1 + 2 * j;
            int y = 2 * (i - 1) * (m - 1) + 2 * j;
            int z = read<int>();
            create(x, y, z);
            create(y, x, z);
        }
    }

    std::fill(dis, dis + t + 10, 0x7f7f7f7f);
    dis[s] = 0;
    q.push(std::make_pair(0, s));

    while (!q.empty()) {
        int p = q.top().second;
        q.pop();

        for (int i = head[p]; i; i = node[i].nxt) {
            int v = node[i].v, w = node[i].w;
            if (dis[v] > dis[p] + w) {
                dis[v] = dis[p] + w;
                q.push(std::make_pair(dis[v], v));
            }
        }
    }

    std::cout << dis[t] << '\n';

    return 0;
}

void create(int u, int v, int w) {
    node[++cnt].v = v;
    node[cnt].w = w;
    node[cnt].nxt = head[u];
    head[u] = cnt;
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