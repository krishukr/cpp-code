#include <cstdio>
#include <iostream>

typedef long long ll;

template <typename T>
T read();

int main() {
    std::ios::sync_with_stdio(false);

    ll a = read<ll>();
    ll b = a - 1000000000000000000ll % a * 9 % a * 9 % a;

    std::cout << b << ' ' << 1000000000000000000ll + b - 1 << '\n';

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
};