#include <cstdio>
#include <iostream>

template <typename T>
T read();

int main() {
    freopen("math.in", "r", stdin);
    freopen("math.out", "w", stdout);

    long long a = read<long long>(), b = read<long long>();
    std::cout << a * b - a - b << '\n';

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