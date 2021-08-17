#include <algorithm>
#include <cstdio>
#include <iostream>

const int MAX_N = 50050;

struct Node {
    int s;
    int e;
    int m;

    bool operator<(const Node &n) const {
        return e < n.e or (e == n.e and s > n.s);
    }
} node[MAX_N];

int se[MAX_N];

template <typename T>
T read();

int main() {
    std::ios::sync_with_stdio(false);

    int k = read<int>(), n = read<int>(), c = read<int>(), ans = 0;

    for (int i = 1; i <= k; i++) {
        node[i].s = read<int>();
        node[i].e = read<int>();
        node[i].m = read<int>();
    }

    std::sort(node + 1, node + k + 1);

    for (int i = 1; i <= k; i++) {
        std::sort(se + 1, se + c + 1, std::greater<int>());

        for (int j = 1; j <= c and node[i].m; j++) {
            if (se[j] <= node[i].s) {
                ans++;
                se[j] = node[i].e;
                node[i].m--;
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