#include <cstdio>
#include <iostream>

typedef long long ll;

template <typename T>
T read();

inline ll quick_pow(ll a, ll b, ll p);

int main() {
    std::ios::sync_with_stdio(false);

    ll n = read<ll>(), k = read<ll>(), m = read<ll>(), p = read<ll>();
    std::cout << (n % p * quick_pow(m, k - 1, p) % p -
                  quick_pow(m, k - 2, p) * (k - 1) % p * ((1 + m) * m / 2 % p) %
                      p +
                  p) %
                     p
              << '\n';

    return 0;
}

inline ll quick_pow(ll a, ll b, ll p) {
    ll res = 1;
    while (b) {
        if (b & 1) {
            res = res * a % p;
        }
        a = a * a % p;
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