#include <cstdio>
#include <cstring>
#include <iostream>

const int MAX_N = 10050;

struct Node {
    int v;
    int w;
    int nxt;
} node[MAX_N];

int head[MAX_N], dep[MAX_N], q[MAX_N];
int cnt = 1, n, m, s, t;

void create(int u, int v, int w);

bool bfs();

int dfs(int x, int flow);

template <typename T>
T read();

int main() {
    std::ios::sync_with_stdio(false);

    n = read<int>(), m = read<int>();
    s = 0, t = n + m + 1;

    while (!std::cin.eof()) {
        int a = read<int>(), b = read<int>();
        if (a == b and a == -1) {
            break;
        } else {
            create(a, b, 1);
            create(b, a, 0);
        }
    }

    for (int i = 1; i <= n; i++) {
        create(s, i, 1);
        create(i, s, 0);
    }
    for (int i = n + 1; i <= m; i++) {
        create(i, t, 1);
        create(t, i, 0);
    }

    int ans = 0;
    while (bfs()) {
        ans += dfs(s, 0x3f3f3f3f);
    }

    if (ans) {
        std::cout << ans << '\n';
        for (int i = 1; i <= n; i++) {
            for (int j = head[i]; j; j = node[j].nxt) {
                int v = node[j].v, w = node[j].w;
                if (v != s and w == 0 and node[j ^ 1].w == 1) {
                    std::cout << i << ' ' << v << '\n';
                }
            }
        }
    } else {
        std::cout << "No Solution!\n";
    }

    return 0;
}

void create(int u, int v, int w) {
    node[++cnt].v = v;
    node[cnt].w = w;
    node[cnt].nxt = head[u];
    head[u] = cnt;
}

bool bfs() {
    memset(dep, 0, sizeof(dep));
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