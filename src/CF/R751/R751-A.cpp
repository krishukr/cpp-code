#include <cstdio>
#include <cstring>
#include <iostream>

template <typename T>
T read();

int main() {
    // std::ios::sync_with_stdio(false);

    int T = read<int>();
    while (T--) {
        std::string s;
        std::cin >> s;

        int n = s.size(), mc = 'z' + 1, idx = 0;

        for (int i = 0; i < n; i++) {
            if (s[i] < mc) {
                mc = s[i];
                idx = i;
            }
        }

        std::cout << (char)(mc) << ' ';
        for (int i = 0; i < n; i++) {
            if (i == idx) {
                continue;
            } else {
                std::cout << (char)(s[i]);
            }
        }
        std::cout << '\n';
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