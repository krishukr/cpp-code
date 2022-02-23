#include <cstdio>
#include <iostream>

typedef unsigned long long ll;

const ll MOD = 998244353;

template <typename T>
T read();

int main() {
    std::ios::sync_with_stdio(false);

    ll n = read<ll>(), k = read<ll>();
    n %= MOD, k %= MOD;
    std::cout << ((((n * n) % MOD - 1 + MOD % MOD) * k % MOD) + 1) % MOD
              << '\n';

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