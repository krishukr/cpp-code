#include <algorithm>
#include <cstdio>
#include <iostream>

typedef long long ll;

ll a[10050];

template <typename T>
T read();

int main() {
    // std::ios::sync_with_stdio(false);

    int t = read<int>(), T = read<int>();

    while (T--) {
        int n = read<int>(), k = read<int>();
        int p = n - k * 2, q = k - p + 1;
        if (p <= 0) {
            q = k;
        }
        if (q < 0) {
            q = k - (n % k) + 1;
        }
        ll ans = 0;
        for (int i = 1; i <= q; i++) {
            ll x = read<int>();
            ans += x;
        }
        for (int i = 1; i <= p; i++) {
            a[i] = read<int>();
        }
        for (int i = p + q + 1; i <= n; i++) {
            ll x = read<int>();
        }
        std::sort(a + 1, a + p + 1, std::greater<int>());
        for (int i = q + 1; i <= k; i++) {
            ans += a[i - 2];
        }
        std::cout << ans << '\n';
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