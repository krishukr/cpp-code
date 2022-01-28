#include <cstdio>
#include <iostream>

typedef long long ll;

ll quick_pow(ll a, ll b, ll m);

template <typename T>
T read();

int main() {
    std::ios::sync_with_stdio(false);

    ll n = read<ll>(), m = read<ll>(), k = read<ll>(), x = read<ll>();

    std::cout << (x % n + m % n * quick_pow(10, k, n) % n) % n << '\n';

    return 0;
}

ll quick_pow(ll a, ll b, ll m) {
    a %= m;
    ll res = 1;
    while (b) {
        if (b & 1) {
            res = res * a % m;
        }
        a = a * a % m;
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