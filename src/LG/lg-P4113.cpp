#include <algorithm>
#include <cstdio>
#include <iostream>

constexpr int MAX_N = 2000050;

struct Q {
    int l;
    int r;
    int p;
} q[MAX_N];

int c[MAX_N], num[MAX_N], ans[MAX_N];
int lst1[MAX_N], lst2[MAX_N];
int n;

inline int low_bit(const int& x) { return x & (-x); }

void mod(int x, const int& w);

int query(int x);

template <typename T = int>
T read();

int main() {
    std::ios::sync_with_stdio(false);

    n = read();
    int _c = read(), m = read();
    for (int i = 1; i <= n; i++) {
        num[i] = read();
    }

    for (int i = 1; i <= m; i++) {
        q[i].l = read();
        q[i].r = read();
        q[i].p = i;
    }
    std::sort(q + 1, q + m + 1,
              [](const Q& x, const Q& y) { return x.r < y.r; });

    int nxt = 1;
    for (int i = 1; i <= m; i++) {
        for (int j = nxt; j <= q[i].r; j++) {
            if (lst1[num[j]]) {
                if (lst2[num[j]]) {
                    mod(lst2[num[j]], 1);
                    mod(lst1[num[j]], -1);
                    lst1[num[j]] = lst2[num[j]];
                } else {
                    mod(lst1[num[j]], 1);
                }
                lst2[num[j]] = j;
            } else {
                lst1[num[j]] = j;
            }
        }
        nxt = q[i].r + 1;
        ans[q[i].p] = query(q[i].r) - query(q[i].l - 1);
    }

    for (int i = 1; i <= m; i++) {
        std::cout << ans[i] << '\n';
    }

    return 0;
}

void mod(int x, const int& w) {
    while (x <= n) {
        c[x] += w;
        x += low_bit(x);
    }
}

int query(int x) {
    int ans = 0;
    while (x >= 1) {
        ans += c[x];
        x -= low_bit(x);
    }
    return ans;
}

template <typename T = int>
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