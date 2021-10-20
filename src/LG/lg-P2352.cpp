#include <algorithm>
#include <cstdio>
#include <iostream>

const int MAX_N = 100050;

#define int long long

int a[MAX_N], b[MAX_N];

template <typename T>
T read();

signed main() {
    std::ios::sync_with_stdio(false);

    int n = read<int>();
    for (int i = 1; i <= n; i++) {
        a[i] = read<int>();
        b[i] = read<int>();
    }
    std::sort(a + 1, a + n + 1);
    std::sort(b + 1, b + n + 1);

    int l = 1, ans = 0;
    for (int i = 1; i <= n; i++) {
        while (l <= n and a[l] <= b[i]) {
            l++;
        }
        ans = std::max(ans, (l - i) * b[i]);
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