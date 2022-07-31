#include <algorithm>
#include <cstdio>
#include <iostream>
#include <queue>

template <typename T>
using pq = std::priority_queue<T, std::vector<T>, std::greater<T>>;

constexpr int MAX_N = 1050;
constexpr int MAX_M = 100050;

struct {
    int v;
    int nxt;
    int w;
} node[MAX_M << 1];

int head[MAX_N << 1];
int cnt;

void create(int u, int v, int w);

int d[MAX_N << 1];

void dij(int s);

template <typename T>
T read();

template <typename T>
void read(T& t);

template <typename T, typename... Args>
void read(T& t, Args&... rest);

int main() {
    std::ios::sync_with_stdio(false);

    int n, m;
    read(n, m);
    for (int i = 1; i <= m; i++) {
        int x, y, z;
        read(x, y, z);
        create(x, y, z);
        create(n + y, n + x, z);
    }
    std::fill(d + 1, d + n + n + 10, 0x3f3f3f3f);

    int a{};
    dij(1);
    dij(n + 1);
    for (int i = 2; i <= n; i++) {
        a += d[i];
    }
    for (int i = n + 2; i <= n + n; i++) {
        a += d[i];
    }
    std::cout << a << '\n';

    return 0;
}

void create(int u, int v, int w) {
    node[++cnt].v = v;
    node[cnt].nxt = head[u];
    node[cnt].w = w;
    head[u] = cnt;
}

void dij(int s) {
    pq<std::pair<int, int>> q;
    q.push({0, s});
    d[s] = 0;
    while (!q.empty()) {
        const auto p = q.top().second;
        q.pop();
        for (int i = head[p]; i; i = node[i].nxt) {
            const auto v = node[i].v, w = node[i].w;
            if (d[v] > d[p] + w) {
                d[v] = d[p] + w;
                q.push({d[v], v});
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