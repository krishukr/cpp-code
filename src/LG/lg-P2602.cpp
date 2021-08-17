#include <iostream>

typedef long long ll;

ll num[10];

constexpr ll n[10] = {1000000,     10000000,     100000000,    1000000000,
                      10000000000, 100000000000, 1000000000000};

inline void w(ll x);

int main() {
    std::ios::sync_with_stdio(false);

    ll a, b;
    std::cin >> a >> b;

    while (a % 1000000 and a < b) {
        w(a);
        a++;
    }
    while (b % 1000000 and a < b) {
        w(b);
        b--;
    }

    while (a != b) {
        for (int i = 0; i <= 9; i++) {
            num[i] += 600000;
        }

        int i = 0;
        while (a / n[i]) {
            num[(a / n[i]) % 10] += 1000000;
            i++;
        }
        a += 1000000;
    }
    w(b);

    for (int i = 0; i <= 9; i++) {
        std::cout << num[i] << ' ';
    }

    return 0;
}

inline void w(ll x) {
    while (x) {
        num[x % 10]++;
        x /= 10;
    }
}