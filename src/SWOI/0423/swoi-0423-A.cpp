#include <algorithm>
#include <cstdio>
#include <iostream>
#include <queue>

const int MAX_N = 2050;

struct Node {
    int v;
    int nxt;
    int w;
} node[MAX_N << 4];

int head[MAX_N];
int cnt;

int dis[MAX_N];

std::priority_queue<std::pair<int, int>, std::vector<std::pair<int, int>>,
                    std::greater<std::pair<int, int>>>
    q;

void craete(int u, int v, int w);

void dij();

char t[MAX_N];
int w[MAX_N], cst[MAX_N][MAX_N];

template <typename T>
T read();

template <typename T>
void read(T& t);

template <typename T, typename... Args>
void read(T& t, Args&... rest);

int main() {
    std::ios::sync_with_stdio(false);

    int n;
    read(n);
    scanf("%s", t + 1);
    for (int i = 1; i <= n; i++) {
        read(w[i]);
    }

    for (int i = 1; i < n; i++) {
        for (int j = 1; j <= i; j++) {
            int u = i - j + 1, v = i + j;
            if (v > n) {
                break;
            }
            if (j == 1) {
                if (t[u] == t[v]) {
                    cst[u][v] = 0;
                } else {
                    cst[u][v] = std::min(w[u], w[v]);
                }
            } else {
                if (t[u] == t[v]) {
                    cst[u][v] = cst[u + 1][v - 1];
                } else {
                    cst[u][v] = std::min(w[u], w[v]) + cst[u + 1][v - 1];
                }
            }
            craete(u, v + 1, cst[u][v]);
        }
    }

    std::fill(dis, dis + n + 10, 0x3f3f3f3f);
    q.push({0, 1});
    dis[1] = 0;
    dij();
    std::cout << dis[n + 1] << '\n';

    return 0;
}

void craete(int u, int v, int w) {
    node[++cnt].v = v;
    node[cnt].w = w;
    node[cnt].nxt = head[u];
    head[u] = cnt;
}

void dij() {
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

template <typename T>
void read(T& t) {
    t = read<T>();
}

template <typename T, typename... Args>
void read(T& t, Args&... rest) {
    t = read<T>();
    read(rest...);
}