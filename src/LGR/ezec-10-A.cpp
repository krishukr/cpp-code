#include <algorithm>
#include <cstdio>
#include <iostream>

const int MAX_N = 1000500;

#define int unsigned long long

int a[MAX_N];

int read();

signed main() {
    std::ios::sync_with_stdio(false);

    int n = read(), m = read(), sum = 0;
    for (int i = 1; i <= n; i++) {
        a[i] = read();
    }
    std::sort(a + 1, a + n + 1);
    int l = a[n];

    while (m) {
        for (int i = n; i > 1; i--) {
            if (m) {
                if (l - a[i] <= m) {
                    m -= l - a[i];
                    a[i] += l - a[i];
                } else {
                    a[i] += m;
                    m = 0;
                }
            } else {
                break;
            }
        }
        if (m) {
            if (m % (n - 1)) {
                l += (m / (n - 1)) + 1;
            } else {
                l += m / (n - 1);
            }
        }
    }

    for (int i = 1; i <= n; i++) {
        sum += a[i];
    }

    if (m) {
    }
    std::cout << sum - a[n] - a[1];

    return 0;
}

inline int read() {
    int x = 0;
    char ch = getchar();
    while (!isdigit(ch)) {
        ch = getchar();
    }
    while (isdigit(ch)) {
        x = x * 10 + ch - 48;
        ch = getchar();
    }
    return x;
}