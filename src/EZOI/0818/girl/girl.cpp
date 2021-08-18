#include <cstdio>
#include <iostream>

template <typename T>
T read();

int main() {
    freopen("girl.in", "r", stdin);
    freopen("girl.out", "w", stdout);

    int n = read<int>();

    if (n <= 2) {
        std::cout << "0\n";
    } else {
        std::cout << "FUCK\n";
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