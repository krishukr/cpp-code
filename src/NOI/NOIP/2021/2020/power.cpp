#include <cstdio>
#include <iostream>

int a[30];

template <typename T>
T read();

int main() {
    std::ios::sync_with_stdio(false);

    int n = read<int>();

    if (n % 2) {
        std::cout << "-1\n";
        return 0;
    } else {
        int ans = 0;
        while (n) {
            if (n & 1) {
                a[ans] = 1 << ans;
            }
            ans++;
            n >>= 1;
        }

        for (int i = ans; i > 0; i--) {
            if (a[i]) {
                std::cout << a[i] << ' ';
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