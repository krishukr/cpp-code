#include <cstdio>
#include <iostream>

typedef long long ll;

template <typename T>
T read();

int main() {
    std::ios::sync_with_stdio(false);

    ll a = read<ll>(), b = read<ll>();
    if (a * a == b * 4) {
        std::cout << "inf\n";
        return 0;
    }

    ll delta = a * a - b * 4, ans = 0;
    for (ll i = (a + 1) % 2 + 1; i * i <= std::abs(delta); i += 2) {
        if (delta % i) {
            continue;
        }
        ll u = i, v = std::abs(delta / i);
        if (delta < 0) {
            u = -u;
        }

        if ((v - u) % 4) {
            continue;
        }
        if (v - (v - u) / 2 < a) {
            break;
        }
        ans++;
    }
    std::cout << ans << '\n';

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