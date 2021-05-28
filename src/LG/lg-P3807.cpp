#include <iostream>

using namespace std;

typedef long long ll;

const int MAX_N = 100001;

ll fact[MAX_N];

ll quick_pow(ll a, ll b, ll p);

ll combination(ll n, ll m, ll p);

ll lucas(ll n, ll m, ll p);

int main() {
    std::ios::sync_with_stdio(false);
    int T;
    cin >> T;
    while (T--) {
        int n, m, p;
        cin >> n >> m >> p;
        fact[0] = 1;
        for (int i = 1; i <= p; i++) {
            fact[i] = (i * fact[i - 1]) % p;
        }
        cout << lucas(n + m, n, p) << endl;
    }

    return 0;
}

ll quick_pow(ll a, ll b, ll p) {
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

ll combination(ll n, ll m, ll p) {
    if (n < m) {
        return 0;
    } else {
        return fact[n] * quick_pow(fact[m], p - 2, p) % p *
               quick_pow(fact[n - m], p - 2, p) % p;
    }
}

ll lucas(ll n, ll m, ll p) {
    if (m == 0) {
        return 1 % p;
    } else {
        return lucas(n / p, m / p, p) * combination(n % p, m % p, p) % p;
    }
}