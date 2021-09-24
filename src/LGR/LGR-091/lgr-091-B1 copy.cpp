#include <algorithm>
#include <cstdio>
#include <iostream>

typedef long long ll;

ll a[10050];

template <typename T>
T read();

int main() {
    // std::ios::sync_with_stdio(false);

    int t = read<int>(), T = read<int>();

    while (T--) {
        int n = read<int>(), k = read<int>();
        ll ans = 0;
        for (int i = 1; i <= k; i++) {
            ll x = read<ll>();
            ans += x;
        }
        std::cout << ans << '\n';
    }

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