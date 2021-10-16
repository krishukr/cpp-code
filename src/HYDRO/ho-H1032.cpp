#include <cstdio>
#include <iostream>

typedef long long ll;

ll quick_pow(int a, int b, int p);

template <typename T>
T read();

int main() {
    std::ios::sync_with_stdio(false);

    int a = read<int>(), b = read<int>(), p = read<int>();
    std::cout << quick_pow(a, b, p) << '\n';

    return 0;
}

ll quick_pow(int a, int b, int p) {
    a %= p;
    ll res = 1;
    while (b) {
        if (b & 1) {
            res = res * a % p;
        }
        a = 1ll * a * a % p;
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