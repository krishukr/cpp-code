#include <algorithm>
#include <cstdio>
#include <iostream>

template <typename T>
T read();

int main() {
    std::ios::sync_with_stdio(false);

    int T = read<int>();
    while (T--) {
        auto* arr = new int[3];
        for (int i = 0; i < 3; i++) {
            arr[i] = read<int>();
        }
        std::sort(arr, arr + 3);

        auto &a = arr[0], &b = arr[1], &c = arr[2];
        if (a + b == c) {
            std::cout << "yes\n";
        } else if (a == b and !(c & 1)) {
            std::cout << "yes\n";
        } else if (b == c and !(a & 1)) {
            std::cout << "yes\n";
        } else {
            std::cout << "no\n";
        }

        delete arr;
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