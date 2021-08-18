#include <cstdio>
#include <iostream>

const int MAX_N = 5050;

struct Node {
    int v;
    int nxt;
} node[MAX_N];

int head[MAX_N], vis[MAX_N];
int cnt;

void dfs(int x);

template <typename T>
T read();

int main() {
    freopen("battle.in", "r", stdin);
    freopen("battle.out", "w", stdout);

    int n = read<int>(), m = read<int>();

    for (int i = 1; i <= m; i++) {
        int x = read<int>(), y = read<int>();

        node[i].v = y;
        node[i].nxt = head[x];
        head[x] = i;
    }

    for (int i = 1; i <= n; i++) {
        if (!vis[i]) {
            dfs(i);
        }
    }
    cnt++;

    std::cout << cnt << ' ' << cnt << '\n';

    fclose(stdin);
    fclose(stdout);
    return 0;
}

void dfs(int x) {
    vis[x] = 1;

    for (int i = head[x]; i; i = node[i].nxt) {
        int v = node[i].v;

        if (!vis[v]) {
            dfs(v);
        } else if (vis[v] == 1) {
            cnt++;
        }
    }

    vis[x] = 2;
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