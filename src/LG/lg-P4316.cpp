#include <cstdio>
#include <iomanip>
#include <iostream>
#include <queue>

constexpr int MAX_N = 100050;

struct {
    int v;
    int nxt;
    int w;
} node[MAX_N << 1];

int head[MAX_N];
int deg[MAX_N], ddg[MAX_N];
int cnt;

void create(int u, int v, int w);

double f[MAX_N];

void topos(int s);

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
        create(y, x, z);
        ddg[x] = ++deg[x];
    }

    topos(n);
    std::cout << std::fixed << std::setprecision(2) << f[1] << '\n';

    return 0;
}

void create(int u, int v, int w) {
    node[++cnt].v = v;
    node[cnt].nxt = head[u];
    node[cnt].w = w;
    head[u] = cnt;
}

void topos(int s) {
    std::queue<int> q;
    q.push(s);
    while (!q.empty()) {
        const auto p = q.front();
        q.pop();
        for (int i = head[p]; i; i = node[i].nxt) {
            const auto v = node[i].v, w = node[i].w;
            f[v] += 1.0 * (f[p] + w) / ddg[v];

            deg[v]--;
            if (!deg[v]) {
                q.push(v);
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