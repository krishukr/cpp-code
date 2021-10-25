#include <cstdio>
#include <iostream>

typedef long long ll;

ll quick_pow(ll a, ll b);

template <typename T>
T read();

int main() {
    std::ios::sync_with_stdio(false);

    int T = read<int>();
    while (T--) {
        int n = read<int>(), c1 = 0, c2 = 0;
        for (int i = 1; i <= n; i++) {
            int x = read<int>();
            if (x == 1) {
                c1++;
            }
            if (x == 0) {
                c2++;
            }
        }

        std::cout << c1 * quick_pow(2, c2) << '\n';
    }

    return 0;
}

ll quick_pow(ll a, ll b) {
    ll res = 1;
    while (b) {
        if (b & 1) {
            res = res * a;
        }
        a = a * a;
        b >>= 1;
    }
    return res;
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