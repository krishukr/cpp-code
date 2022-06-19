#include <cstdio>
#include <iostream>

constexpr int MAX_N = 300050;

int d[MAX_N];

struct Node {
    int v;
    int nxt;
    int x;
} node[MAX_N << 1];

int head[MAX_N];
int cnt;

void create(int u, int v, int x);

int fa[MAX_N];

int find(int x) { return (fa[x] == x ? x : (fa[x] = find(fa[x]))); }

bool ans[MAX_N];
int tot;

bool dfs(int x, int f);

template <typename T>
T read();

template <typename T>
void read(T& t);

template <typename T, typename... Args>
void read(T& t, Args&... rest);

int main() {
    std::ios::sync_with_stdio(false);

    int n, m, sum{};
    read(n, m);
    for (int i = 1; i <= n; i++) {
        fa[i] = i;
    }
    for (int i = 1; i <= n; i++) {
        read(d[i]);
        if (d[i] == 1) {
            sum ^= 1;
        }
    }

    for (int i = 1; i <= m; i++) {
        int x, y;
        read(x, y);
        if (find(x) != find(y)) {
            fa[find(x)] = find(y);
            create(x, y, i);
            create(y, x, i);
        }
    }

    for (int i = 1; i <= n; i++) {
        if (d[i] == -1) {
            if (sum) {
                sum ^= 1;
                d[i] = 1;
            } else {
                d[i] = 0;
            }
        }
    }

    if (sum) {
        std::cout << -1 << '\n';
    } else {
        dfs(1, 0);
        std::cout << tot << '\n';
        for (int i = 1; i <= n; i++) {
            if (ans[i]) {
                std::cout << i << '\n';
            }
        }
    }

    return 0;
}

void create(int u, int v, int x) {
    node[++cnt].v = v;
    node[cnt].nxt = head[u];
    node[cnt].x = x;
    head[u] = cnt;
}

bool dfs(int x, int f) {
    int s = d[x];
    for (int i = head[x]; i; i = node[i].nxt) {
        int v = node[i].v, idx = node[i].x;
        if (v == f) {
            continue;
        }
        if (dfs(v, x)) {
            tot++;
            ans[idx] = true;
            s ^= 1;
        }
    }
    return s;
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