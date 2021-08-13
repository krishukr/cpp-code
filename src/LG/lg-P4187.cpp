#include <cstdio>
#include <iostream>

typedef long long ll;

const ll MOD = 1e9 + 7;
const int MAX_N = 1000050;

ll d[MAX_N], s[MAX_N];

template <typename T>
T read();

int main() {
    std::ios::sync_with_stdio(false);

    int n = read<int>(), m = read<int>(), k = read<int>();
    ll ans = 1;

    for (int i = 1; i <= n; i++) {
        ans = ans * m % MOD;
    }

    d[0] = s[0] = 1;
    for (int i = 1; i <= n; i++) {
        if (i < k) {
            d[i] = d[i - 1] * m % MOD;
        } else {
            d[i] = (s[i - 1] - s[i - k] + MOD) % MOD * (m - 1) % MOD;
        }
        s[i] = (s[i - 1] + d[i]) % MOD;
    }

    std::cout << (ans - d[n] + MOD) % MOD << '\n';

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