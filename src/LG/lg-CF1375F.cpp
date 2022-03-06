#include <cstdio>
#include <iostream>

typedef long long ll;

ll a[4];

int main() {
    // std::ios::sync_with_stdio(false);

    for (int i = 1; i <= 3; i++) {
        std::cin >> a[i];
    }
    std::cout << "First\n" << (ll)1e10 << std::endl;

    int i1;
    std::cin >> i1;
    a[i1] += 1e10;
    ll t1 = 3 * a[i1] - a[1] - a[2] - a[3];
    std::cout << t1 << std::endl;

    int i2;
    std::cin >> i2;
    a[i2] += t1;
    std::cout << a[i1] - a[6 - i1 - i2] << std::endl;

    return 0;
}