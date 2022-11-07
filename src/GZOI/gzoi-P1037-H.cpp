#include <cstdio>
#include <cstring>
#include <iostream>
#include <queue>
#include <utility>
#include <vector>

template <typename T>
using pq = std::priority_queue<T, std::vector<T>, std::greater<T>>;

constexpr int MAX_N = 90050;
constexpr int MAX_M = 1000050;

struct {
    int v;
    int nxt = 0xafafafaf;
    int w;
} node[MAX_M];

int head[MAX_N];
int cnt;

void create(int u, int v, int w);

int d[MAX_N];
bool vis[MAX_N];

template <typename T>
T read();

template <typename T>
void read(T& t);

template <typename T, typename... Args>
void read(T& t, Args&... rest);

int main() {
    std::ios::sync_with_stdio(false);

    int n, s, e, m{};
    read(n, s, e);
    for (int i = 1; i <= n; i++) {
        int x, y, z;
        read(x, y, z);
        m = std::max(m, y + 1);
        create(x, y + 1, z);
    }
    for (int i = s + 1; i <= m; i++) {
        create(i, i - 1, 0);
    }

    memset(d, 0x3f, sizeof(d));
    pq<std::pair<int, int>> q;
    q.push({0, s});
    d[s] = 0;
    while (!q.empty()) {
        const auto p = q.top().second;
        q.pop();
        if (vis[p]) {
            continue;
        }
        vis[p] = true;

        for (int i = head[p]; i != 0xafafafaf; i = node[i].nxt) {
            const auto &v = node[i].v, &w = node[i].w;
            if (d[v] > d[p] + w) {
                d[v] = d[p] + w;
                q.push({d[v], v});
            }
        }
    }

    std::cout << (d[e + 1] == 0x3f3f3f3f ? -1 : d[e + 1]) << '\n';

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
    char ch = getchar_unlocked();
    while (!isdigit(ch)) {
        if (ch == '-') f = -1;
        ch = getchar_unlocked();
    }
    while (isdigit(ch)) {
        x = x * 10 + ch - 48;
        ch = getchar_unlocked();
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