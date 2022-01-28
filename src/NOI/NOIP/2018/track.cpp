#include <cstdio>
#include <iostream>

const int MAX_N = 50050;

struct Node {
    int v;
    int nxt;
    int w;
} node[MAX_N];

int head[MAX_N];
int cnt, ans;

void create(int u, int v, int w);

int dfs(int x, int f);

template <typename T>
T read();

int main() {
    freopen("track.in", "r", stdin);
    freopen("track.out", "w", stdout);

    int n = read<int>(), m = read<int>();
    for (int i = 1; i < n; i++) {
        int u = read<int>(), v = read<int>(), w = read<int>();
        create(u, v, w);
        create(v, u, w);
    }

    dfs(1, 0);
    std::cout << ans << '\n';

    fclose(stdin);
    fclose(stdout);
    return 0;
}

int dfs(int x, int f) {
    int a1 = 0, a2 = 0;
    for (int i = head[x]; i; i = node[i].nxt) {
        int v = node[i].v;
        if (v == f) {
            continue;
        }
        a2 = std::max(a2, dfs(v, x) + node[i].w);
        if (a1 < a2) {
            std::swap(a1, a2);
        }
    }
    ans = std::max(ans, a1 + a2);
    return a1;
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

// 20 pts