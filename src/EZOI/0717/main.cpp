#include <cmath>
#include <cstdio>
#include <iostream>

template <typename T>
T read();

int main() {
    freopen("main.in", "r", stdin);
    freopen("main.out", "w", stdout);

    for (int kkk = 1; kkk <= 10; kkk++) {
        int n = read<int>(), ans = 0;
        for (int i = 1; i <= n; i++) {
            int x = read<int>();
            ans ^= x;
        }
        if (ans) {
            std::cout << "YES\n";
        } else {
            std::cout << "NO\n";
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