#include <cstdio>
#include <iostream>

typedef long long ll;

const int MOD = 1e9 + 9;

ll quick_pow(ll a, ll b);

template <typename T>
T read();

int main() {
    std::ios::sync_with_stdio(false);

    int t = read<int>();
    while (t--) {
        ll x = read<ll>();
        std::cout << quick_pow(x, x - 1) << '\n';
    }

    return 0;
}

ll quick_pow(ll a, ll b) {
    a %= MOD;
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