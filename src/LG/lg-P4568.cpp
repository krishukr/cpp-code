#include <cstdio>
#include <cstring>
#include <iostream>
#include <queue>

template <typename T>
using pq = std::priority_queue<T, std::vector<T>, std::greater<T>>;

constexpr int MAX_N = 200050;

struct {
    int v;
    int nxt;
    int w;
} node[MAX_N << 4];

int head[MAX_N];
int cnt;

void create(int u, int v, int w);

int d[MAX_N];

template <typename T>
T read();

template <typename T>
void read(T& t);

template <typename T, typename... Args>
void read(T& t, Args&... rest);

int main() {
    std::ios::sync_with_stdio(false);

    int n, m, K, S, T;
    read(n, m, K, S, T);
    for (int i = 1; i <= m; i++) {
        int x, y, z;
        read(x, y, z);
        for (int j = 0; j < K; j++) {
            create(x + n * j, y + n * j, z);
            create(y + n * j, x + n * j, z);
            create(x + n * j, y + n * (j + 1), 0);
            create(y + n * j, x + n * (j + 1), 0);
        }
        create(x + n * K, y + n * K, z);
        create(y + n * K, x + n * K, z);
    }

    memset(d, 0x3f, sizeof(d));
    pq<std::pair<int, int>> q;
    d[S] = 0;
    q.push({d[S], S});
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

    int r{0x3f3f3f3f};
    for (int i = 0; i <= K; i++) {
        r = std::min(r, d[T + n * i]);
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