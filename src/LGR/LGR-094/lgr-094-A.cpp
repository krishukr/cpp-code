#include <cmath>
#include <cstdio>
#include <iostream>

template <typename T>
T read();

int main() {
    std::ios::sync_with_stdio(false);

    int t = read<int>();
    while (t--) {
        int n = read<int>(), m = read<int>(), a = 1, b = n;

        for (int i = std::sqrt(n); i > 0; i--) {
            if (!(n % i)) {
                a = i;
                b = n / a;
                break;
            }
        }

        if (2 * (a + 1 + b + 1) <= m) {
            std::cout << "Good\n";
        } else {
            std::cout << "Miss\n";
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