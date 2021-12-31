#include <algorithm>
#include <cstdio>
#include <iostream>

const int MAX_N = 100050;

struct Node {
    int l;
    int r;
    int v;
} node[MAX_N];

int dp[MAX_N];

template <typename T>
T read();

int main() {
    std::ios::sync_with_stdio(false);

    int T = read<int>();
    while (T--) {
        int n = read<int>();
        for (int i = 1; i <= n; i++) {
            int x = read<int>(), y = read<int>(), w = read<int>(),
                h = read<int>(), d = read<int>();
            node[i] = (Node){x + y, x + y + w + h, d};
        }

        std::sort(node + 1, node + n + 1,
                  [](const Node& a, const Node& b) -> bool {
                      return (a.l == b.l) ? (a.r < b.r) : (a.l < b.l);
                  });

        std::fill(dp, dp + 1500, -0x3f3f3f3f);

        for (int i = 1; i <= n; i++) {
            if (node[i].l < dp[node[i].v ^ 1]) {
                std::cout << 2 << '\n';
                goto ed;
            }
            dp[node[i].v] = std::max(dp[node[i].v], node[i].r);
        }
        std::cout << 1 << '\n';

    ed:;
    }

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