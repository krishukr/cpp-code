#include <cstdio>
#include <cstring>
#include <iostream>

template <typename T>
T read();

int main() {
    // std::ios::sync_with_stdio(false);

    int T = read<int>();
    while (T--) {
        int n = read<int>(), m = read<int>();
        std::string s;
        std::cin >> s;

        if (m > n) {
            std::string r;
            int t = n - 1, j = 0;
            while (r.length() < m) {
                if (j < t) {
                    r.push_back('0');
                    j++;
                } else {
                    r.push_back('1');
                    j = 0;
                }
            }
            std::cout << r << '\n';
        } else {
            std::cout << -1 << '\n';
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