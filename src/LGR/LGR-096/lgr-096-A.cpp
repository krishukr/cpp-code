#include <algorithm>
#include <cstdio>
#include <iostream>

#define int long long

template <typename T>
T read();

signed main() {
    std::ios::sync_with_stdio(false);

    int n = read<int>(), ans = 0;
    int x = read<int>();
    ans += x;
    for (int i = 1; i < n; i++) {
        x = read<int>();
        ans += std::abs(x);
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