#include <cstdio>
#include <iostream>

int x, y;

void expand_gcd(int a, int b);

template <typename T>
T read();

int main() {
    std::ios::sync_with_stdio(false);

    int a = read<int>(), b = read<int>();

    expand_gcd(a, b);
    x = (x % b + b) % b;

    std::cout << x << '\n';

    return 0;
}

void expand_gcd(int a, int b) {
    if (!b) {
        x = 1;
        y = 0;
        return;
    } else {
        expand_gcd(b, a % b);
        int t = x;
        x = y;
        y = t - a / b * y;
    }
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