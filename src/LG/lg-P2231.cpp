#include <cstdio>
#include <iostream>

typedef long long ll;

ll quick_pow(ll a, ll b);

template <typename T>
T read();

int main() {
    std::ios::sync_with_stdio(false);

    ll n = read<ll>(), m = read<ll>();
    ll fac = m, res = 1;

    for (int i = 2; i * i <= m; i++) {
        if (!(m % i)) {
            res *= quick_pow(i, n) - 1;
            fac /= i;
            while (!(m % i)) {
                m /= i;
            }
        }
    }

    if (m > 1) {
        res *= quick_pow(m, n) - 1;
        fac /= m;
    }

    std::cout << res * quick_pow(fac, n) << '\n';

    return 0;
}

ll quick_pow(ll a, ll b) {
    ll res = 1;
    while (b) {
        if (b & 1) {
            res = res * a;
        }
        a = a * a;
        b >>= 1;
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