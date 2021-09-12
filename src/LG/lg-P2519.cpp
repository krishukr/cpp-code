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
} q[MAX_N], ans[MAX_N];

int w[MAX_N], dp[MAX_N];
int cnt, num, j = 1;

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
        int l = q[i].l, r = q[i].r;
        if (l != q[i - 1].l or r != q[i - 1].r) {
            num++;
        }
        w[num] = std::min(w[num] + 1, r - l + 1);
        ans[num] = q[i];
    }

    for (int i = 1; i <= n; i++) {
        dp[i] = dp[i - 1];
        while (j <= num and ans[j].r == i) {
            dp[i] = std::max(dp[i], dp[ans[j].l - 1] + w[j]);
            j++;
        }
    }

    std::cout << n - dp[n] << '\n';

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