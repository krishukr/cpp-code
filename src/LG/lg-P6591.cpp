#include <cstdio>
#include <iostream>

constexpr int MAX_N = 1000050;

struct {
    int v;
    int nxt;
} node[MAX_N << 1];

int head[MAX_N];
int cnt;

void create(int u, int v);

int deg[MAX_N], siz[MAX_N];
bool ans[MAX_N];

void dfs(int x, int f);

int n;

template <typename T>
T read();

template <typename T>
void read(T& t);

template <typename T, typename... Args>
void read(T& t, Args&... rest);

int main() {
    std::ios::sync_with_stdio(false);

    read(n);
    for (int i = 1; i < n; i++) {
        int x, y;
        read(x, y);
        create(x, y);
        create(y, x);
        deg[x]++;
        deg[y]++;
    }
    for (int i = 1; i <= n; i++) {
        if (deg[i] == 1) {
            ans[i] = true;
        }
    }

    dfs(1, 0);
    for (int i = 1; i <= n; i++) {
        if (ans[i]) {
            std::cout << i << ' ';
        }
    }
    std::cout << '\n';

    return 0;
}

void create(int u, int v) {
    node[++cnt].v = v;
    node[cnt].nxt = head[u];
    head[u] = cnt;
}

void dfs(int x, int f) {
    siz[x] = 1;
    int s{};
    bool t = true;
    for (int i = head[x]; i; i = node[i].nxt) {
        const auto v = node[i].v;
        if (v == f) {
            continue;
        }
        dfs(v, x);
        siz[x] += siz[v];

        if (s) {
            if (siz[v] != s) {
                t = false;
            }
        } else {
            s = siz[v];
        }
    }
    if (siz[x] != n and n - siz[x] != s) {
        t = false;
    }
    ans[x] |= t;
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