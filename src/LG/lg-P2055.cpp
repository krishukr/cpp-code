#include <algorithm>
#include <cstdio>
#include <cstring>
#include <iostream>

const int MAX_N = 500050;

struct Node {
    int v;
    int nxt;
    int w;
} node[MAX_N];

int head[MAX_N], dep[MAX_N], q[MAX_N];
int cnt = 1;
int ans;
int n, s, t;

void init(int n);

void create(int u, int v, int w);

bool bfs();

int dfs(int x, int flow);

template <typename T>
T read();

int main() {
    std::ios::sync_with_stdio(false);

    int T = read<int>();
    while (T--) {
        n = read<int>(), s = n + n + 2, t = n + n + 3;
        auto *a = new int[n + 10]{};
        auto *b = new int[n + 10]{};
        int tot = 0;

        for (int i = 1; i <= n; i++) {
            a[i] = read<int>();
            if (a[i]) {
                create(i + n, t, 1);
                create(t, i + n, 0);
            }
        }
        for (int i = 1; i <= n; i++) {
            b[i] = read<int>();
            if ((a[i] and !b[i]) or !a[i]) {
                tot++;
                create(s, i, 1);
                create(i, s, 0);
            }
        }

        for (int i = 1; i <= n; i++) {
            for (int j = 1; j <= n; j++) {
                int x = read<int>();
                if (x or i == j) {
                    create(i, j + n, 1);
                    create(j + n, i, 0);
                }
            }
        }

        while (bfs()) {
            ans += dfs(s, 0x3f3f3f3f);
        }

        if (ans >= tot) {
            std::cout << "^_^\n";
        } else {
            std::cout << "T_T\n";
        }

        init(n);
    }

    return 0;
}

void init(int n) {
    std::fill(node, node + n + n + 10, (Node){0, 0, 0});
    std::fill(head, head + n + n + 10, 0);
    std::fill(q, q + n + n + 10, 0);
    cnt = 1;
    ans = 0;
}

bool bfs() {
    std::fill(dep, dep + n + n + 10, 0);
    int l, r;
    l = r = 1;
    q[l] = s;
    dep[s] = 1;

    while (l <= r) {
        int u = q[l++];
        for (int i = head[u]; i; i = node[i].nxt) {
            if (node[i].w and !dep[node[i].v]) {
                dep[node[i].v] = dep[u] + 1;
                q[++r] = node[i].v;
            }
        }
    }

    return dep[t];
}

int dfs(int x, int flow) {
    if (x == t) {
        return flow;
    }
    int tot = 0;

    for (int i = head[x]; i and flow; i = node[i].nxt) {
        int y = node[i].v;
        if (node[i].w and dep[y] == dep[x] + 1) {
            int res = dfs(y, std::min(node[i].w, flow));
            node[i].w -= res;
            node[i ^ 1].w += res;
            flow -= res;
            tot += res;
        }
    }

    if (tot == 0) {
        dep[x] = 0;
    }
    return tot;
}

void create(int u, int v, int w) {
    node[++cnt].v = v;
    node[cnt].w = w;
    node[cnt].nxt = head[u];
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