#include <cstdio>
#include <iostream>

typedef long long ll;

inline ll solve(ll n);

template <typename T>
T read();

int main() {
    std::ios::sync_with_stdio(false);

    int T = read<int>();
    while (T--) {
        ll n = read<ll>();
        std::cout << solve(n) << '\n';
    }

    return 0;
}

inline ll solve(ll n) {
    if (n == 1 or n == 2) {
        return 0;
    } else if (n & 1) {
        return solve(n / 2) + solve(n / 2 + 1) + 1;
    } else {
        return solve(n / 2) * 2;
    }
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