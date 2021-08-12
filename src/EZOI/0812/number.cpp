#include <cmath>
#include <cstdio>
#include <iostream>
#include <set>

typedef long long ll;

const ll MOD = 1000391835649;

template <typename T>
T read();

int main() {
    freopen("number.in", "r", stdin);
    freopen("number.out", "w", stdout);

    std::set<ll> v;
    ll n = read<ll>(), ans = 0;

    ll r1 = (ll)(sqrt(n));
    ll r2 = (ll)(pow(n, 1.0 / 3));
    for (ll i = 1; i <= r1; i++) {
        for (ll j = 1; j <= r2; j++) {
            ll r = i * i * j * j * j;
            if (r <= n) {
                v.insert(r);
            }
        }
    }

    for (auto i : v) {
        ans += i;
        ans %= MOD;
    }

    std::cout << v.size() << '\n' << ans << '\n';

    fclose(stdin);
    fclose(stdout);
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
