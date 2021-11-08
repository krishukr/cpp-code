#include <cstdio>
#include <iostream>

typedef long long ll;

const int MAX_N = 100050;
const int MOD = 998244353;

int a[MAX_N];
ll fact[MAX_N];

ll quick_pow(ll a, ll b);

ll combination(ll n, ll m);

template <typename T>
T read();

int main() {
    freopen("cook.in", "r", stdin);
    freopen("cook.out", "w", stdout);

    int n = read<int>(), m = read<int>();
    fact[0] = 1;
    for (int i = 1; i <= n; i++) {
        a[i] = read<int>();
        fact[i] = fact[i - 1] * i;
        fact[i] %= MOD;
    }

    while (m--) {
        int op = read<int>(), l = read<int>(), r = read<int>();
        if (op == 1) {
            int x = read<int>();
            for (int i = l; i <= r; i++) {
                a[i] += x;
            }
        } else {
            int x = read<int>(), y = read<int>(), ans = 0;
            for (int i = l; i <= r; i++) {
                if (a[i] <= x) {
                    ans++;
                }
            }

            ll res = 0;
            for (int i = 0; i <= y; i++) {
                if (i > ans) {
                    break;
                }
                res += combination(ans, i);
                res %= MOD;
            }
            std::cout << res << '\n';
        }
    }

    fclose(stdin);
    fclose(stdout);
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

ll combination(ll n, ll m) {
    if (n < m) {
        return 0;
    } else {
        return fact[n] * quick_pow(fact[m], MOD - 2) % MOD *
               quick_pow(fact[n - m], MOD - 2) % MOD;
    }
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