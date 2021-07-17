#include <algorithm>
#include <cstdio>
#include <iostream>

const int MAX_N = 1000050;

struct Query {
    int l;
    int r;
    int p;

    bool operator<(const Query &u) const { return r < u.r; }
} q[MAX_N];

int c[MAX_N], num[MAX_N], vis[MAX_N], ans[MAX_N];
int n;

int low_bit(int x);

void mod(int pos, int w);

int query(int pos);

int read();

int main() {
    std::ios::sync_with_stdio(false);

    n = read();
    for (int i = 1; i <= n; i++) {
        num[i] = read();
    }

    int m = read();
    for (int i = 1; i <= m; i++) {
        q[i].l = read();
        q[i].r = read();
        q[i].p = i;
    }
    std::sort(q + 1, q + m + 1);

    int nxt = 1;
    for (int i = 1; i <= m; i++) {
        for (int j = nxt; j <= q[i].r; j++) {
            if (vis[num[j]]) {
                mod(vis[num[j]], -1);
            }
            mod(j, 1);
            vis[num[j]] = j;
        }
        nxt = q[i].r + 1;
        ans[q[i].p] = query(q[i].r) - query(q[i].l - 1);
    }

    for (int i = 1; i <= m; i++) {
        std::cout << ans[i] << '\n';
    }

    return 0;
}

int low_bit(int x) { return x & (-x); }

void mod(int pos, int w) {
    while (pos <= n) {
        c[pos] += w;
        pos += low_bit(pos);
    }
}

int query(int pos) {
    int ans = 0;
    while (pos >= 1) {
        ans += c[pos];
        pos -= low_bit(pos);
    }
    return ans;
}

int read() {
    int x = 0, f = 1, ch = getchar();
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