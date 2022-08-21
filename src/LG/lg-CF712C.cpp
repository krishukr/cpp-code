#include <cstdio>
#include <cstring>
#include <iostream>
#include <queue>

constexpr int MAX_N = 5050;

struct {
    int v;
    int nxt;
    int w;
} node[MAX_N];

int head[MAX_N];
int cnt;

void create(int u, int v, int w);

int ind[MAX_N];
int f[MAX_N][MAX_N], g[MAX_N][MAX_N];
int n, m, k, ans;

void topos();

void out(int x, int d);

template <typename T>
T read();

template <typename T>
void read(T& t);

template <typename T, typename... Args>
void read(T& t, Args&... rest);

int main() {
    std::ios::sync_with_stdio(false);

    memset(f, 0x3f, sizeof(f));
    f[1][1] = 0;
    read(n, m, k);
    for (int i = 1; i <= m; i++) {
        int x, y, z;
        read(x, y, z);
        ind[y]++;
        create(x, y, z);
    }

    topos();
    std::cout << ans << '\n';
    out(n, ans);
    std::cout << '\n';

    return 0;
}

void create(int u, int v, int w) {
    node[++cnt].v = v;
    node[cnt].nxt = head[u];
    node[cnt].w = w;
    head[u] = cnt;
}

void topos() {
    std::queue<int> q;
    for (int i = 1; i <= n; i++) {
        if (!ind[i]) {
            q.push(i);
        }
    }

    while (!q.empty()) {
        const auto p = q.front();
        q.pop();
        for (int i = head[p]; i; i = node[i].nxt) {
            const auto v = node[i].v, w = node[i].w;
            for (int j = 1; j <= n; j++) {
                if (f[v][j] > f[p][j - 1] + w and f[p][j - 1] + w <= k) {
                    f[v][j] = f[p][j - 1] + w;
                    g[v][j] = p;
                    if (ans < j and v == n) {
                        ans = j;
                    }
                }
            }
            ind[v]--;
            if (!ind[v]) {
                q.push(v);
            }
        }
    }
}

void out(int x, int d) {
    if (x > 1) {
        out(g[x][d], d - 1);
    }
    std::cout << x << ' ';
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