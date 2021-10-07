#include <cstdio>
#include <iomanip>
#include <iostream>

typedef long long ll;

template <typename T>
T read();

int main() {
    std::ios::sync_with_stdio(false);

    ll x = read<ll>(), y = read<ll>(), ans = 0, l, r;
    ll n = std::min(x, y);

    for (l = 1; l <= n; l = r + 1) {
        r = x / (x / l);
        ans += (x % l + x % r) * (r - l + 1) / 2;
    }
    if (x < y) {
        ans += (y - x) * x;
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