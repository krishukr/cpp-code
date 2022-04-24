#include <cstdio>
#include <cstring>
#include <iostream>

constexpr int MAX_N = 100050;

struct Node {
    int v;
    int nxt;
} node[MAX_N << 1];

int head[MAX_N];
int cnt;

void create(int u, int v);

int mxd[MAX_N], mnd[MAX_N];
int dis[MAX_N];
bool rot[MAX_N];

void dfs1(int x, int f);

void dfs2(int x, int f);

template <typename T>
T read();

template <typename T>
void read(T& t);

template <typename T, typename... Args>
void read(T& t, Args&... rest);

int main() {
    std::ios::sync_with_stdio(false);

    memset(mxd, -0x3f, sizeof(mxd));
    memset(mnd, -0x3f, sizeof(mnd));
    memset(dis, -0x3f, sizeof(dis));

    int n, m, d;
    read(n, m, d);
    for (int i = 1; i <= m; i++) {
        rot[read<int>()] = true;
    }
    for (int i = 1; i < n; i++) {
        int x, y;
        read(x, y);
        create(x, y);
        create(y, x);
    }

    dfs1(1, 0);
    dfs2(1, 0);

    int ans = (mxd[1] <= d and mnd[1] <= d);
    for (int i = 2; i <= n; i++) {
        ans += (dis[i] <= d and mxd[i] <= d);
    }
    std::cout << ans << '\n';

    return 0;
}

void create(int u, int v) {
    node[++cnt].v = v;
    node[cnt].nxt = head[u];
    head[u] = cnt;
}

void dfs1(int x, int f) {
    if (rot[x]) {
        mxd[x] = mnd[x] = 0;
    }
    for (int i = head[x]; i; i = node[i].nxt) {
        int v = node[i].v;
        if (v == f) {
            continue;
        }
        dfs1(v, x);
        if (mxd[x] < mxd[v] + 1) {
            mnd[x] = mxd[x];
            mxd[x] = mxd[v] + 1;
        } else if (mnd[x] < mxd[v] + 1) {
            mnd[x] = mxd[v] + 1;
        }
    }
}

void dfs2(int x, int f) {
    for (int i = head[x]; i; i = node[i].nxt) {
        int v = node[i].v;
        if (v == f) {
            continue;
        }
        if (mxd[x] == mxd[v] + 1) {
            dis[v] = std::max(dis[x] + 1, mnd[x] + 1);
        } else {
            dis[v] = std::max(dis[x] + 1, mxd[x] + 1);
        }
        dfs2(v, x);
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