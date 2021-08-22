#include <cstdio>
#include <iostream>

typedef long long ll;

ll qu(ll x);

template <typename T>
T read();

int main() {
    std::ios::sync_with_stdio(false);

    ll l = read<ll>(), r = read<ll>();

    std::cout << qu(r) - qu(l - 1) << '\n';

    return 0;
}

ll qu(ll x) {
    if (x <= 9) {
        return x;
    }

    ll a = x % 10, b = x, res = x / 10 + 9;

    while (b >= 10) {
        b /= 10;
    }

    if (b > a) {
        res--;
    }
    return res;
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