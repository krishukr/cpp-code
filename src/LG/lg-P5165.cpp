#include <cstdio>
#include <iostream>

typedef long long ll;

const int MOD = 1e9 + 7;

ll quick_pow(ll a, ll b);

inline ll inv(const ll &x);

template <typename T>
T read();

int main() {
    std::ios::sync_with_stdio(false);

    ll n = read<ll>(), m = read<ll>(), p = read<ll>(), q = read<ll>();
    ll lp = p * inv(q) % MOD, rp = 1 - lp + MOD % MOD;

    return 0;
}

ll quick_pow(ll a, ll b) {
    ll res = 1;
    while (b) {
        if (b & 1) {
            res = res * a % MOD;
        }
        a = a * a % MOD;
        b >>= 1;
    }
    return res;
}

inline ll inv(const ll &x) { return quick_pow(x, MOD - 2); }

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