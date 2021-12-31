#include <cstdio>
#include <iostream>

const int MAX_N = 10000050;

struct Node {
    int v;
    int w;
    int nxt;
} node[MAX_N << 1];

int head[MAX_N];
int cnt;

bool vis[MAX_N];
int dis[MAX_N];
int mxd, mnd, ans, res;

void create(int u, int v, int w);

template <typename T>
T gcd(T m, T n);

void dfs(int x, int d);

template <typename T>
T read();

int main() {
    std::ios::sync_with_stdio(false);

    int n = read<int>(), m = read<int>();
    for (int i = 1; i <= m; i++) {
        int x = read<int>(), y = read<int>();
        create(x, y, 1);
        create(y, x, -1);
    }

    for (int i = 1; i <= n; i++) {
        if (!vis[i]) {
            mxd = 0;
            mnd = 0x3f3f3f3f;
            dfs(i, 0);
            res += mxd - mnd + 1;
        }
    }

    if (ans) {
        if (ans < 3) {
            printf("-1 -1\n");
        } else {
            for (int i = 3; i <= ans; i++) {
                if (!(ans % i)) {
                    printf("%d %d\n", ans, i);
                    break;
                }
            }
        }
    } else {
        if (res < 3) {
            printf("-1 -1\n");
        } else {
            printf("%d %d\n", res, 3);
        }
    }

    return 0;
}

void create(int u, int v, int w) {
    node[++cnt].v = v;
    node[cnt].nxt = head[u];
    head[u] = cnt;
    node[cnt].w = w;
}

void dfs(int x, int d) {
    if (dis[x]) {
        ans = gcd(ans, std::abs(d - dis[x]));
        return;
    }

    dis[x] = d;
    vis[x] = true;
    mxd = std::max(mxd, d);
    mnd = std::min(mnd, d);

    for (int i = head[x]; i; i = node[i].nxt) {
        int v = node[i].v, w = node[i].w;
        dfs(v, d + w);
    }
}

template <typename T>
T gcd(T m, T n) {
    while (n != 0) {
        T t = m % n;
        m = n;
        n = t;
    }
    return m;
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