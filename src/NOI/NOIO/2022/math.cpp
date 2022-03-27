#include <algorithm>
#include <cstdio>
#include <iostream>

template <typename T>
T read();

int main() {
    freopen("math.in", "r", stdin);
    freopen("math.out", "w", stdout);

    int T = read<int>();
    while (T--) {
        int x = read<int>(), z = read<int>();
        if (z < x) {
            std::cout << -1 << '\n';
            continue;
        }

        int p = z / x;
        bool flag = false;
        for (int i = 1; i <= p; i++) {
            if (p % i == 0 and std::__gcd(x, i) == p / i) {
                std::cout << i << '\n';
                flag = true;
                break;
            }
        }

        if (!flag) {
            std::cout << -1 << '\n';
        }
    }

    fclose(stdin);
    fclose(stdout);
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