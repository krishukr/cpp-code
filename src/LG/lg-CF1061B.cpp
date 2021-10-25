#include <algorithm>
#include <cstdio>
#include <iostream>

typedef long long ll;

const int MAX_N = 100050;

int a[MAX_N];

template <typename T>
T read();

int main() {
    std::ios::sync_with_stdio(false);

    int n = read<int>(), m = read<int>();
    ll s = 0, p = 0;
    for (int i = 1; i <= n; i++) {
        a[i] = read<int>();
        s += a[i];
    }
    std::sort(a + 1, a + n + 1, std::greater<int>());
    for (int i = 1; i <= n; i++) {
        p++;
        p -= a[i] - a[i + 1];
        s -= a[i] - a[i + 1];
        p = std::max(0ll, p);
    }

    std::cout << s - p << '\n';

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