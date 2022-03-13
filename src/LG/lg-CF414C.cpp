#include <algorithm>
#include <cstdio>
#include <iostream>

typedef long long ll;

int a[(1 << 20) + 50];
ll s[31][2];
ll p[31];

void solve(int l, int r, int d);

template <typename T>
T read();

int main() {
    std::ios::sync_with_stdio(false);

    p[0] = 1;
    for (int i = 1; i <= 30; i++) {
        p[i] = p[i - 1] * 2;
    }

    int n = read<int>();
    for (int i = 0; i < p[n]; i++) {
        a[i] = read<int>();
    }
    solve(0, p[n], n);

    int m = read<int>();
    while (m--) {
        int x = read<int>();
        while (x--) {
            std::swap(s[x + 1][0], s[x + 1][1]);
        }

        ll ans = 0;
        for (int i = 0; i <= n; i++) {
            ans += s[i][0];
        }
        std::cout << ans << '\n';
    }

    return 0;
}

void solve(int l, int r, int d) {
    int mid = (l + r) / 2;
    if (l + 1 < r) {
        solve(l, mid, d - 1);
        solve(mid, r, d - 1);

        ll ans = 0;
        for (int i = l; i < mid; i++) {
            ans += std::lower_bound(a + mid, a + r, a[i]) - a - mid;
        }
        s[d][0] += ans;

        ans = 0;
        for (int i = mid; i < r; i++) {
            ans += std::lower_bound(a + l, a + mid, a[i]) - a - l;
        }
        s[d][1] += ans;

        std::sort(a + l, a + r);
    }
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