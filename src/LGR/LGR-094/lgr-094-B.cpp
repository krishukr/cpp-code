#include <cmath>
#include <cstdio>
#include <iostream>

typedef long long ll;

ll p;

ll f(ll x);

template <typename T>
T read();

int main() {
    std::ios::sync_with_stdio(false);

    int t = read<int>();
    while (t--) {
        ll n = read<ll>();
        p = read<ll>();

        if (p == 1) {
            std::cout << 0 << '\n';
        } else {
            std::cout << f(n) << '\n';
        }
    }

    return 0;
}

ll f(ll x) {
    if (x == 0) {
        return 0;
    }
    return x - f(x / p);
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