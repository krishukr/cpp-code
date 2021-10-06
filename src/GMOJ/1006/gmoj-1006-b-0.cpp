#include <algorithm>
#include <cstdio>
#include <iostream>

const int MAX_N = 100050;

struct Node {
    int d;
    int r;
    int p;

    bool operator<(const Node &n) const { return d > n.d; }
} q[MAX_N];

int ans[MAX_N], crt[MAX_N];

template <typename T>
T read();

int main() {
    std::ios::sync_with_stdio(false);

    int n = read<int>();
    for (int i = 1; i <= n; i++) {
        q[i].d = read<int>();
        q[i].r = read<int>();
        q[i].p = i;
    }

    std::sort(q + 1, q + n + 1);
    crt[1] = q[1].r;
    ans[q[1].p] = 1;

    for (int i = 2; i <= n; i++) {
        int l = 1, r = i;
        while (l <= r) {
            int mid = (l + r) / 2;
            if (crt[mid] > q[i].r) {
                l = mid + 1;
            } else {
                r = mid - 1;
            }
        }
        crt[l] = q[i].r;
        ans[q[i].p] = l;
    }

    for (int i = 1; i <= n; i++) {
        std::cout << ans[i] << '\n';
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