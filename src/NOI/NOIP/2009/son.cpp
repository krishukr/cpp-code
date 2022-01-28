#include <cstdio>
#include <iostream>

int gcd(int a, int b);

template <typename T>
T read();

int main() {
    std::ios::sync_with_stdio(false);

    int T = read<int>();

    while (T--) {
        int a0 = read<int>(), a1 = read<int>();
        int b0 = read<int>(), b1 = read<int>();
        int x = a0 / a1, y = b1 / b0, ans = 0;

        for (int i = 1; i * i <= b1; i++) {
            if (!(b1 % i)) {
                if (!(i % a1) and gcd(i / a1, x) == 1 and gcd(y, b1 / i) == 1) {
                    ans++;
                }

                int j = b1 / i;
                if (i == j) {
                    continue;
                }

                if (!(j % a1) and gcd(j / a1, x) == 1 and gcd(y, b1 / j) == 1) {
                    ans++;
                }
            }
        }

        std::cout << ans << '\n';
    }

    return 0;
}

int gcd(int a, int b) {
    if (b == 0) return a;
    return gcd(b, a % b);
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