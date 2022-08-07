#include <cstdio>
#include <cstring>
#include <iostream>
#include <queue>

using ll = long long;

template <typename T>
using pq = std::priority_queue<T, std::vector<T>, std::greater<T>>;

constexpr int MAX_N = 20000050;

struct {
    int v;
    int nxt;
    int w;
} node[MAX_N];

int head[MAX_N];
int cnt;

void create(int u, int v, int w);

int dis[MAX_N];

template <typename T>
T read();

template <typename T>
void read(T& t);

template <typename T, typename... Args>
void read(T& t, Args&... rest);

int main() {
    std::ios::sync_with_stdio(false);

    int n, m, k, p, q, b;
    read(n, m, k, p, q, b);
    for (int i = 1; i <= m; i++) {
        int x, y, z;
        read(x, y, z);
        for (int j = 0; j <= k; j++) {
            create(x + n * j, y + n * j, z);
            create(y + n * j, x + n * j, z);
        }
        for (int j = 0; j < k; j++) {
            create(x + n * j, y + n * (j + 1), (1ll * p * z / q) + b);
            create(y + n * j, x + n * (j + 1), (1ll * p * z / q) + b);
        }
    }

    {
        memset(dis, 0x3f, sizeof(dis));
        pq<std::pair<int, int>> q;
        q.push({0, 1});
        dis[1] = 0;
        while (!q.empty()) {
            const auto p = q.top().second;
            q.pop();
            for (int i = head[p]; i; i = node[i].nxt) {
                const auto v = node[i].v, w = node[i].w;
                if (dis[v] > dis[p] + w) {
                    dis[v] = dis[p] + w;
                    q.push({dis[v], v});
                }
            }
        }
    }

    int r{0x3f3f3f3f};
    for (int i = 0; i <= k; i++) {
        r = std::min(r, dis[n + n * i]);
    }
    std::cout << r << '\n';

    return 0;
}

void create(int u, int v, int w) {
    node[++cnt].v = v;
    node[cnt].nxt = head[u];
    node[cnt].w = w;
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

template <typename T>
void read(T& t) {
    t = read<T>();
}

template <typename T, typename... Args>
void read(T& t, Args&... rest) {
    t = read<T>();
    read(rest...);
}