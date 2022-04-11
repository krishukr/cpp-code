#include <cstdio>
#include <iostream>

template <typename T = int>
T read();

int main() {
    std::ios::sync_with_stdio(false);

    int T = read();
    while (T--) {
        int n = read(), ans = 0, sum = 0;
        for (int i = 1; i <= n; i++) {
            int x = read();
            ans ^= x;
            sum += x;
        }

        std::cout << (sum == n ? (n & 1 ? "Brother" : "John")
                               : (ans ? "John" : "Brother"))
                  << '\n';
    }

    return 0;
}

template <typename T = int>
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