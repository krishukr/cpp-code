#include <iostream>

typedef long long ll;

const int MAX_N = 100050;
const int MOD = 1e9 + 7;

ll fact(int x);

int main() {
    int n, m, tot = 0;
    std::cin >> n >> m;
    ll ans = 1;

    for (int i = 1; i <= m; i++) {
        int e;
        std::cin >> e;
        tot += e;
        ans *= fact(e);
        ans %= MOD;
    }

    ans *= fact(n - tot + m);
    ans %= MOD;

    std::cout << ans << '\n';

    return 0;
}

ll fact(int x) {
    ll res = 1;
    for (int i = 1; i <= x; i++) {
        res *= i;
        res %= MOD;
    }
    return res;
}