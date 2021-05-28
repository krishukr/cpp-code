#include <iostream>

typedef long long ll;

const int MAX_N = 11;

using namespace std;

ll ex_gcd(ll a, ll b, ll &x, ll &y);

ll crt(ll n, const ll a[], const ll m[]);

int main() {
    ll n, a[MAX_N], b[MAX_N];
    cin >> n;
    for (int i = 0; i < n; i++) {
        cin >> a[i] >> b[i];
    }
    cout << crt(n, b, a);

    return 0;
}

ll ex_gcd(ll a, ll b, ll &x, ll &y) {
    if (b == 0) {
        x = 1;
        y = 0;
        return a;
    }
    ll ans = ex_gcd(b, a % b, y, x);
    y -= (a / b) * x;
    return ans;
}

ll crt(ll n, const ll a[], const ll m[]) {
    ll M = 1, ans = 0, Mi, ti, y;
    for (int i = 0; i < n; i++) {
        M *= m[i];
    }
    for (int i = 0; i < n; i++) {
        Mi = M / m[i];
        ex_gcd(Mi, m[i], ti, y);
        ans = (ans + a[i] * ti * Mi) % M;
    }
    return (ans + M) % M;
}