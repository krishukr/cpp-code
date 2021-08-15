#include <algorithm>
#include <climits>
#include <cstdio>
#include <iostream>

const int MAX_N = 100000;

struct Node {
    int x;
    int y;

    bool operator<(const Node &n) const { return x < n.x; }
} node[MAX_N];

int dp[MAX_N];

template <typename T>
T read();

int main() {
    std::ios::sync_with_stdio(false);

    int n = read<int>();

    for (int i = 1; i <= n; i++) {
        node[i].x = read<int>();
        node[i].y = read<int>();
    }
    std::sort(node + 1, node + n + 1);

    for (int i = 2; i <= n; i++) {
        int d = node[i].x - node[i].y;
        int x = std::lower_bound(node + 1, node + n + 1, (Node){d, 0}) - node;

        dp[i] = dp[x - 1] + i - x;
    }

    int ans = INT_MAX;
    for (int i = n; i > 0; i--) {
        ans = std::min(ans, dp[i] + n - i);
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