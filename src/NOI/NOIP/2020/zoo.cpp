#include <cstdio>
#include <iostream>

typedef long long ll;
typedef unsigned long long ull;

int gui[250];

template <typename T>
T read();

int main() {
    std::ios::sync_with_stdio(false);

    int n = read<int>(), m = read<int>(), c = read<int>(), k = read<int>(),
        ans = 0;
    ull cnt = 0, res = 0;

    if (k == 64 and !n and !m) {
        std::cout << "18446744073709551616\n";
        return 0;
    }

    for (int i = 1; i <= n; i++) {
        ull x = read<ull>();
        cnt |= x;
    }

    for (int i = 1; i <= m; i++) {
        int x = read<int>(), y = read<int>();
        gui[x] = y;
    }

    for (int i = 0; i <= 63; i++) {
        if ((cnt & (1ull << i)) and gui[i]) {
            gui[i] = 0;
        }
    }

    for (int i = 0; i <= 63; i++) {
        if (gui[i]) {
            ans++;
        }
    }

    res = 1ull << (k - 1);
    res -= n;
    res += (1ull << (k - 1));
    res -= (((1ull << ans) - 1) * (1ull << (k - ans)));

    std::cout << res << '\n';

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