#include <cstdio>
#include <iostream>

typedef long long ll;

const int MAX_N = 10000050;
const int MOD = 998244353;

ll inv[MAX_N], s[MAX_N];

template <typename T>
T read();

int main() {
    std::ios::sync_with_stdio(false);

    inv[1] = s[1] = 1;
    for (int i = 2; i <= MAX_N - 40; i++) {
        inv[i] = (MOD - MOD / i) * inv[MOD % i] % MOD;
        s[i] = (s[i - 1] + inv[i]) % MOD;
    }

    int T = read<int>(), ans = 0;
    while (T--) {
        int n = read<int>(), k = read<int>();
        ans ^= (inv[n] * (s[n] - s[n - k] + MOD)) % MOD;
    }
    std::cout << ans << '\n';

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