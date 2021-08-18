#include <cstdio>
#include <iostream>

typedef long long ll;

template <typename T>
T read();

int main() {
    std::ios::sync_with_stdio(false);

    ll k = read<int>(), m = read<int>(), res = -1, i, j, n;

    for (i = 1; i <= k; i *= 10) {
        res += k / i - i + 1;
    }

    if (res >= m or k - (i / 10) == 0 and res < m - 1) {
        std::cout << "0\n";
    } else {
        for (j = k - (i / 10), n = k; res < m - 1; j *= 10, res += j) {
            n *= 10;
        }

        std::cout << std::max(n - res + m - 2, k) << '\n';
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