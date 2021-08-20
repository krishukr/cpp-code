#include <cstdio>
#include <iostream>

int buc[605];

template <typename T>
T read();

int main() {
    std::ios::sync_with_stdio(false);

    int n = read<int>(), w = read<int>();

    for (int i = 1; i <= n; i++) {
        int x = read<int>();
        buc[x]++;

        int res = 0;
        for (int j = 600; j >= 0; j--) {
            res += buc[j];
            if (res >= std::max(1, i * w / 100)) {
                std::cout << j << ' ';
                break;
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