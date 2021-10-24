#include <algorithm>
#include <cstdio>
#include <iostream>

typedef long long ll;

const int MAX_N = 100050;

ll l[MAX_N], r[MAX_N];

template <typename T>
T read();

int main() {
    std::ios::sync_with_stdio(false);

    int n = read<int>(), m = read<int>();
    ll ans = 0;
    for (int i = 1; i <= n; i++) {
        l[i] = read<ll>();
        r[i] = read<ll>();
        ans += std::abs(r[i] - l[i]);
    }

    l[0] = m;
    std::sort(l, l + n + 1);
    std::sort(r, r + n + 1);

    for (int i = 0; i <= n; i++) {
        ans += std::abs(r[i] - l[i]);
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