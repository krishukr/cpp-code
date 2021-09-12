#include <algorithm>
#include <cstdio>
#include <iostream>

const int MAX_N = 100010;

struct Node {
    int l;
    int r;

    bool operator<(const Node &n) const {
        return (r == n.r ? l < n.l : r < n.r);
    }
} q[MAX_N];

int cnt, num;

template <typename T>
T read();

int main() {
    std::ios::sync_with_stdio(false);

    int n = read<int>();

    for (int i = 1; i <= n; i++) {
        int x = read<int>(), y = read<int>();
        if (x + y >= n) {
            continue;
        } else {
            q[++cnt].l = x + 1;
            q[cnt].r = n - y;
        }
    }

    std::sort(q + 1, q + cnt + 1);

    for (int i = 1; i <= cnt; i++) {
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