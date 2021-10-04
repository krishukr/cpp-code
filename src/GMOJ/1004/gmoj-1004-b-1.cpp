#include <algorithm>
#include <cstdio>
#include <iostream>

const int MAX_N = 100050;

struct Node {
    int ch[2];
    int f;
} tree[MAX_N];

int w[MAX_N], dfn[MAX_N], dp[MAX_N];
int cnt, len;

void dfs(int x);

template <typename T>
T read();

int main() {
    std::ios::sync_with_stdio(false);

    int n = read<int>();
    for (int i = 1; i <= n; i++) {
        w[i] = read<int>();
    }

    for (int i = 2; i <= n; i++) {
        tree[i].f = read<int>();
        int x = read<int>();
        tree[tree[i].f].ch[x] = i;
    }

    dfs(1);
    for (int i = 1; i <= n; i++) {
        if (dfn[i] >= dp[len]) {
            dp[++len] = dfn[i];
        } else {
            *std::upper_bound(dp + 1, dp + len + 1, dfn[i]) = dfn[i];
        }
    }
    std::cout << n - len << '\n';

    return 0;
}

void dfs(int x) {
    if (tree[x].ch[0]) {
        dfs(tree[x].ch[0]);
    }
    cnt++;
    dfn[cnt] = w[x] - cnt;
    if (tree[x].ch[1]) {
        dfs(tree[x].ch[1]);
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