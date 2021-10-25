#include <cstdio>
#include <iostream>

typedef long long ll;

template <typename T>
T read();

int main() {
    std::ios::sync_with_stdio(false);

    int t = read<int>();
    while (t--) {
        ll a = read<ll>(), b = read<ll>(), c = read<ll>();
        std::cout << (a + b * 2 + c * 3) % 2 << '\n';
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