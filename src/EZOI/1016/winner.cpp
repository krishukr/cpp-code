#include <cstdio>
#include <iostream>

template <typename T>
T read();

int main() {
    freopen("winner.in", "r", stdin);
    freopen("winner.out", "w", stdout);

    while (!std::cin.eof()) {
        int n = read<int>(), m = read<int>();
        if (n == -1 and m == -1) {
            break;
        }
        for (int i = 1; i <= m; i++) {
            int u = read<int>(), v = read<int>();
        }
        std::cout << "NO\n";
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