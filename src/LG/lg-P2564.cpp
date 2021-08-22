#include <algorithm>
#include <cstdio>
#include <iostream>
#include <queue>

const int MAX_N = 1000050;

struct Node {
    int c;
    int p;

    bool operator<(const Node &n) const { return p < n.p; }
} node[MAX_N];

int vis[65];
int cnt;

template <typename T>
T read();

int main() {
    std::ios::sync_with_stdio(false);

    int n = read<int>(), k = read<int>();

    for (int i = 1; i <= k; i++) {
        int t = read<int>();
        for (int j = 1; j <= t; j++) {
            node[++cnt].p = read<int>();
            node[cnt].c = i;
        }
    }

    std::sort(node + 1, node + n + 1);
    std::queue<Node> q;
    int res = 0, ans = 0x3f3f3f3f;

    for (int i = 1; i <= n; i++) {
        q.push(node[i]);
        vis[q.back().c]++;

        if (vis[q.back().c] == 1) {
            res++;
        }
        while (res == k) {
            Node b = q.back(), f = q.front();

            ans = std::min(ans, b.p - f.p);
            q.pop();
            vis[f.c]--;
            if (!vis[f.c]) {
                res--;
            }
        }
    }

    std::cout << ans << '\n';

    return 0;
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