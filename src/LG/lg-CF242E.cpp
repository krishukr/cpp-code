#include <cstdio>
#include <iostream>

typedef long long ll;

const int MAX_N = 100050;

int a[MAX_N];

template <typename T>
T read();

int main() {
    std::ios::sync_with_stdio(false);

    int n = read<int>();
    for (int i = 1; i <= n; i++) {
        a[i] = read<int>();
    }

    int m = read<int>();
    for (int i = 1; i <= m; i++) {
        int op = read<int>(), e;
        if (op == 1) {
            int l = read<int>(), r = read<int>();
            ll res = 0;
            for (int i = l; i <= r; i += 8) {
                res += a[i];
                res += a[i + 1];
                res += a[i + 2];
                res += a[i + 3];
                res += a[i + 4];
                res += a[i + 5];
                res += a[i + 6];
                res += a[i + 7];
                e = i;
            }
            for (int i = e; i <= e + 7; i++) {
                if (i > r) {
                    res -= a[i];
                }
            }
            std::cout << res << '\n';
        } else {
            int l = read<int>(), r = read<int>(), x = read<int>();
            for (int i = l; i <= r; i += 8) {
                a[i] ^= x;
                a[i + 1] ^= x;
                a[i + 2] ^= x;
                a[i + 3] ^= x;
                a[i + 4] ^= x;
                a[i + 5] ^= x;
                a[i + 6] ^= x;
                a[i + 7] ^= x;
                e = i;
            }
            for (int i = e; i <= e + 7; i++) {
                if (i > r) {
                    a[i] ^= x;
                }
            }
        }
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