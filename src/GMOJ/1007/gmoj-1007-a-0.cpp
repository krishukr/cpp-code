#include <algorithm>
#include <cstdio>
#include <iostream>

typedef long long ll;

const int MAX_N = 100050;

ll s[MAX_N], t[MAX_N];

template <typename T>
T read();

int main() {
    std::ios::sync_with_stdio(false);

    ll n = read<ll>(), m = read<ll>(), ans = 0;
    s[0] = m;

    for (int i = 1; i <= n; i++) {
        s[i] = read<ll>();
        t[i] = read<ll>();
        ans += std::abs(s[i] - t[i]);
    }

    std::sort(s, s + n + 1);
    std::sort(t, t + n + 1);

    for (int i = 0; i <= n; i++) {
        ans += std::abs(s[i] - t[i]);
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