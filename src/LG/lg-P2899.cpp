#include <cstdio>
#include <iostream>
#include <queue>

const int MAX_N = 10050;

struct Node {
    int v;
    int nxt;
} node[MAX_N << 1];

int head[MAX_N << 1];
int cnt;

struct Que {
    int idx;
    int dep;
    int fa;

    bool operator<(const Que &x) const { return dep < x.dep; }
} qu[MAX_N];

bool vis[MAX_N];

void create(int u, int v);

void dfs(int x, int f, int d);

template <typename T>
T read();

int main() {
    std::ios::sync_with_stdio(false);

    std::priority_queue<Que> q;
    int n = read<int>();

    for (int i = 1; i < n; i++) {
        int x = read<int>(), y = read<int>();
        create(x, y);
        create(y, x);
    }

    dfs(1, 0, 1);
    for (int i = 1; i <= n; i++) {
        q.push(qu[i]);
    }

    int res = 0;
    while (!q.empty()) {
        Que l = q.top();
        q.pop();

        if (vis[l.idx]) {
            continue;
        }
        vis[l.idx] = vis[l.fa] = true;

        res++;
        for (int i = head[l.fa]; i; i = node[i].nxt) {
            int v = node[i].v;
            vis[v] = true;
        }
    }

    std::cout << res << '\n';

    return 0;
}

void create(int u, int v) {
    node[++cnt].v = v;
    node[cnt].nxt = head[u];
    head[u] = cnt;
}

void dfs(int x, int f, int d) {
    qu[x] = (Que){x, d, f};
    for (int i = head[x]; i; i = node[i].nxt) {
        int v = node[i].v;
        if (v == f) {
            continue;
        }
        dfs(v, x, d + 1);
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