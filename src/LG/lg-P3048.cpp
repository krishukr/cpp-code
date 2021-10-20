#include <cstdio>
#include <iostream>

int r[50];

template <typename T>
T read();

int main() {
    std::ios::sync_with_stdio(false);

    int n = read<int>(), k = read<int>();
    for (int i = 1; i <= k; i++) {
        r[i] = i;
    }

    for (int i = 2; i <= n; i++) {
        for (int j = 1; j <= k; j++) {
            if (r[j] + 1 != r[j + 1]) {
                ++r[j];
                break;
            }
            r[j] = j;
        }
    }

    for (int i = r[k]; i > 0; i--) {
        if (r[k] == i) {
            std::cout << 1;
            k--;
        } else {
            std::cout << 0;
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