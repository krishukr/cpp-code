#include <cmath>
#include <cstdio>
#include <iostream>

const int MAX_N = 500050;

struct Node {
    int v;
    int nxt;
} node[MAX_N];

int head[MAX_N], fa[MAX_N], idx[MAX_N], dp[MAX_N], ans[MAX_N];
int cnt, n;

void create(int u, int v);

void dfs(int x, int f);

int work(int x);

template <typename T>
T read();

int main() {
    std::ios::sync_with_stdio(false);

    n = read<int>();

    for (int i = 1; i < n; i++) {
        int x = read<int>(), y = read<int>();
        create(x, y);
        create(y, x);
    }

    cnt = 0;
    dfs(1, 0);
    ans[1] = n;
    int esp = sqrt(n * log2(n));

    for (int i = 2; i <= esp; i++) {
        ans[i] = work(i);
    }

    for (int i = esp + 1; i <= n; i++) {
        int t = work(i);
        int l = i, r = n, a = i;

        while (l < r - 1) {
            int mid = (l + r) >> 1;
            if (work(mid) == t) {
                l = mid;
                a = std::max(a, mid);
            } else {
                r = mid;
            }
        }
        for (; i <= a; i++) {
            ans[i] = t;
        }
        i--;
    }

    for (int i = 1; i <= n; i++) {
        std::cout << ans[i] << '\n';
    }

    return 0;
}

void create(int u, int v) {
    node[++cnt].v = v;
    node[cnt].nxt = head[u];
    head[u] = cnt;
}

void dfs(int x, int f) {
    fa[x] = f;
    for (int i = head[x]; i; i = node[i].nxt) {
        int v = node[i].v;
        if (v == f) {
            continue;
        }
        dfs(v, x);
    }
    idx[++cnt] = x;
}

int work(int x) {
    int res = 0;
    for (int i = 1; i <= n; i++) {
        dp[i] = 1;
    }
    for (int i = 1; i <= n; i++) {
        int u = idx[i];
        int f = fa[u];
        if (f and dp[u] != -1 and dp[f] != -1) {
            if (dp[u] + dp[f] >= x) {
                res++;
                dp[f] = -1;
            } else {
                dp[f] = std::max(dp[f], dp[u] + 1);
            }
        }
    }
    return res;
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