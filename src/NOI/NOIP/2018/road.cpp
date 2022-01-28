#include <cstdio>
#include <iostream>

template <typename T>
T read();

int main() {
    freopen("road.in", "r", stdin);
    freopen("road.out", "w", stdout);

    int n = read<int>(), res = 0, last = 0;

    while (n--) {
        int a = read<int>();
        if (a > last) {
            res += a - last;
        }
        last = a;
    }

    std::cout << res << '\n';

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