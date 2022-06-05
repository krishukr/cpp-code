#include <climits>
#include <cstdio>
#include <cstring>
#include <iostream>

using ll = long long;

constexpr int MAX_N = 100050;
constexpr ll INF = 1e12;

struct Node {
    int v;
    int nxt;
} node[MAX_N << 1];

int head[MAX_N];
int cnt;

void create(int u, int v);

int p[MAX_N];
ll f[2][MAX_N];

void dfs(int x, int fa);

template <typename T>
T read();

template <typename T>
void read(T& t);

template <typename T, typename... Args>
void read(T& t, Args&... rest);

int main() {
    freopen("defense.in", "r", stdin);
    freopen("defense.out", "w", stdout);
    std::ios::sync_with_stdio(false);

    int n, m;
    read(n, m);
    char opc = getchar();
    while (opc != 'A' and opc != 'B' and opc != 'C') {
        opc = getchar();
    }
    int opi;
    read(opi);

    for (int i = 1; i <= n; i++) {
        read(p[i]);
    }
    for (int i = 1; i < n; i++) {
        int x, y;
        read(x, y);
        create(x, y);
        create(y, x);
    }

    while (m--) {
        int a, x, b, y;
        read(a, x, b, y);
        f[1 - x][a] = INF;
        f[1 - y][b] = INF;
        dfs(1, 0);

        const auto ans = std::min(f[0][1], f[1][1]);
        std::cout << (ans < INF ? ans : -1) << '\n';

        memset(f, 0, sizeof(f));
    }

    std::cout << std::flush;
    fclose(stdin);
    fclose(stdout);
    return 0;
}

void create(int u, int v) {
    node[++cnt].v = v;
    node[cnt].nxt = head[u];
    head[u] = cnt;
}

void dfs(int x, int fa) {
    f[1][x] += p[x];
    for (int i = head[x]; i; i = node[i].nxt) {
        int v = node[i].v;
        if (v == fa) {
            continue;
        }
        dfs(v, x);
        f[0][x] += f[1][v];
        f[1][x] += std::min(f[0][v], f[1][v]);
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