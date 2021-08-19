#include <algorithm>
#include <cstdio>
#include <iostream>

const int MAX_N = 200050;

struct Node {
    int x;
    int f;

    bool operator<(const Node &n) const { return x < n.x; }
} node[MAX_N];

template <typename T>
T read();

int main() {
    // std::ios::sync_with_stdio(false);

    int n = read<int>(), l = 0, ans = 0;

    for (int i = 1; i <= n; i++) {
        int x = read<int>();
        char op;
        std::cin >> op;

        if (op == 'L') {
            node[i * 2 - 1] = (Node){l - x, 1};
            node[i * 2] = (Node){l, -1};
            l -= x;
        } else {
            node[i * 2 - 1] = (Node){l, 1};
            node[i * 2] = (Node){l + x, -1};
            l += x;
        }
    }
    std::sort(node + 1, node + 2 * n + 1);
    l = node[1].f;

    for (int i = 2; i <= 2 * n; i++) {
        if (l >= 2) {
            ans += node[i].x - node[i - 1].x;
        }
        l += node[i].f;
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