#include <cstdio>
#include <iostream>

typedef long long ll;

template <typename T>
T read();

int main() {
    std::ios::sync_with_stdio(false);

    ll x = read<ll>(), y = read<ll>(), ans = x * y, l, r;

    for (l = 1; l <= x; l = r + 1) {
        r = (y / l ? std::min(y / (y / l), x) : x);
        ans -= (y / l) * (l + r) * (r - l + 1) / 2;
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