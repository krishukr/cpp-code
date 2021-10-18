#include <cstdio>
#include <iostream>

typedef long long ll;

const int MAX_N = 1000050;
const int MOD = 1e9 + 7;

ll fac[MAX_N];
int n;

void init(int n);

ll quick_pow(ll a, ll b);

ll sum(int x);

template <typename T>
T read();

int main() {
    freopen("bubble.in", "r", stdin);
    freopen("bubble.out", "w", stdout);

    n = read<int>();
    init(n);

    ll res = 0;
    for (int i = 1; i < n; i++) {
        res += i * ((sum(i) % MOD - sum(i - 1) % MOD + MOD) % MOD);
        res %= MOD;
    }

    std::cout << res * quick_pow(fac[n], MOD - 2) % MOD << '\n';

    fclose(stdin);
    fclose(stdout);
    return 0;
}

void init(int n) {
    fac[0] = 1;
    for (int i = 1; i <= n; i++) {
        fac[i] = fac[i - 1] * i;
        fac[i] %= MOD;
    }
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

ll sum(int x) { return fac[x] * quick_pow(x + 1, n - x) % MOD; }

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