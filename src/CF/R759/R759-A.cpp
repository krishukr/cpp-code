#include <cstdio>
#include <cstring>
#include <iostream>

template <typename T>
T read();

int main() {
    int T = read<int>();
    while (T--) {
        int n = read<int>();
        char s[105] = {};
        std::cin >> (s + 1);

        for (int i = 1; i <= n; i++) {
            for (int j = i + 1; j <= n; j++) {
                bool flag = false;
                for (int k = 0; k < (j - i + 1) / 2; k++) {
                    if (s[i + k] != s[j - k]) {
                        flag = true;
                        break;
                    }
                }
                if (!flag) {
                    std::cout << "NO\n";
                    goto ed;
                }
            }
        }
        std::cout << "YES\n";

    ed:;
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