#include <cstdio>
#include <iostream>

typedef long long ll;

int a[1050];

int main() {
    std::ios::sync_with_stdio(false);

    int n;
    std::cin >> n;
    ll ans = 0;

    for (int i = 1; i <= n; i++) {
        std::cin >> a[i];
    }

    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= n; j++) {
            int x;
            std::cin >> x;

            if (i > j) {
                ans += 1ll * x * std::min(a[i], a[j]);
            }
        }
    }

    std::cout << ans << '\n';

    return 0;
}
