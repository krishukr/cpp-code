#include <cstdio>
#include <iostream>

typedef long long ll;

int main() {
    std::ios::sync_with_stdio(false);

    ll x;
    while (std::cin >> x) {
        std::cout << (1 + x * (x - 1) / 2 +
                      x * (x - 1) * (x - 2) * (x - 3) / 24)
                  << '\n';
    }

    return 0;
}