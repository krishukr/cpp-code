#include <cstdio>
#include <iostream>

typedef long long ll;

const int MAX_N = 100050;

ll s[MAX_N];

template <typename T>
T read();

int main() {
    std::ios::sync_with_stdio(false);

    int n = read<int>(), m = read<int>();
    ll ans = 0;

    for (int i = std::max(n, m); i > 0; i--) {
        s[i] = (ll)(n / i) * (m / i);
        for (int j = i * 2; j <= std::max(n, m); j += i) {
            s[i] -= s[j];
        }
        ans += (i * 2 - 1) * s[i];
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