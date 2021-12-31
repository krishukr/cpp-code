#include <cstdio>
#include <iostream>

template <typename T>
T read();

int main() {
    std::ios::sync_with_stdio(false);

    int T = read<int>();
    while (T--) {
        double x1 = read<int>(), p1 = read<int>();
        double x2 = read<int>(), p2 = read<int>();

        while (x1 > 9) {
            x1 /= 10;
            p1++;
        }
        while (x2 > 9) {
            x2 /= 10;
            p2++;
        }

        if (p1 < p2) {
            std::cout << '<' << '\n';
        } else if (p1 > p2) {
            std::cout << '>' << '\n';
        } else {
            if (x1 < x2) {
                std::cout << '<' << '\n';
            } else if (x1 > x2) {
                std::cout << '>' << '\n';
            } else {
                std::cout << '=' << '\n';
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