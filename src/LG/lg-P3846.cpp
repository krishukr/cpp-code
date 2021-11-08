#include <cmath>
#include <cstdio>
#include <iostream>
#include <map>

typedef long long ll;

ll quick_pow(ll a, ll b, ll p);

ll bsgs(ll a, ll b, ll p);

template <typename T>
T read();

int main() {
    std::ios::sync_with_stdio(false);

    ll p = read<ll>(), a = read<ll>(), b = read<ll>();
    ll r = bsgs(a, b, p);

    if (r == -1) {
        std::cout << "no solution\n";
    } else {
        std::cout << r << '\n';
    }

    return 0;
}

ll quick_pow(ll a, ll b, ll p) {
    ll res = 1;
    a %= p;
    while (b) {
        if (b & 1) {
            res = res * a % p;
        }
        a = a * a % p;
        b >>= 1;
    }
    return res;
}

ll bsgs(ll a, ll b, ll p) {
    std::map<ll, ll> hsh{};
    b %= p;
    ll sq = std::sqrt(p) + 1;

    for (ll i = 0; i < sq; i++) {
        hsh[b * quick_pow(a, i, p) % p] = i;
    }
    a = quick_pow(a, sq, p);

    if (!a) {
        return (b ? -1 : 1);
    }

    for (ll i = 1; i <= sq; i++) {
        ll w = quick_pow(a, i, p);
        ll j = (hsh.find(w) == hsh.end() ? -1 : hsh[w]);

        if (j >= 0 and i * sq - j >= 0) {
            return i * sq - j;
        }
    }
    return -1;
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