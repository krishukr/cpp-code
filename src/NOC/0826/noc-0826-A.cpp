#include <cstdio>
#include <iostream>

using ll = long long;

constexpr int MAX_N = 1000050;

struct {
    int v;
    int nxt;
    int w;
} node[MAX_N << 1];

int head[MAX_N];
int cnt;
int v[MAX_N];

void create(int u, int v, int w);

int cc{};

ll dfs(int x, int f);

bool check(int x);

int n, W;

template <typename T>
T read();

template <typename T>
void read(T& t);

template <typename T, typename... Args>
void read(T& t, Args&... rest);

int main() {
    std::ios::sync_with_stdio(false);

    read(n, W);
    for (int i = 1; i < n; i++) {
        read(v[i + 1]);
    }
    for (int i = 1; i < n; i++) {
        int x, y, z;
        read(x, y, z);
        create(x, y, z);
        create(y, x, z);
    }

    int l{}, r = 1e9 + 10, a{};
    while (l <= r) {
        const auto mid = (l + r) >> 1;
        if (check(mid)) {
            r = mid - 1;
            a = mid;
        } else {
            l = mid + 1;
        }
    }
    std::cout << l << '\n';

    return 0;
}

void create(int u, int v, int w) {
    node[++cnt].v = v;
    node[cnt].nxt = head[u];
    node[cnt].w = w;
    head[u] = cnt;
}

ll dfs(int x, int f) {
    ll res{};
    for (int i = head[x]; i; i = node[i].nxt) {
        const auto v = node[i].v, w = node[i].w;
        if (v == f or cc < w) {
            continue;
        }
        res += ::v[v];
        res += dfs(v, x);
    }
    return res;
}

bool check(int x) {
    cc = x;
    return dfs(1, 0) >= W;
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