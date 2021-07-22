#include <cmath>
#include <cstdio>
#include <iostream>

template <typename T>
T read();

int main() {
    freopen("fk.in", "r", stdin);
    freopen("fk.out", "w", stdout);

    int n = read<int>();
    int b = 1, i = 1;
    while (n >= (i * i)) {
        i++;
        while (!(n % (i * i))) {
            b *= i;
            n /= i * i;
        }
    }
    std::cout << b << ' ' << n << '\n';

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