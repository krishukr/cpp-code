#include <cstdio>
#include <cstring>
#include <iostream>

const int MAX_N = 1000050;

int a[MAX_N];

inline int read();

int main() {
    std::ios::sync_with_stdio(false);

    int T = read();
    while (T--) {
        int n = read(), ans = 0;
        for (int i = 1; i <= n; i++) {
            a[i] = read();
        }
        a[n + 1] = n + 1;
        for (int i = 1; i <= n; i++) {
            if ((a[i - 1] != i - 1 and a[i + 1] != i + 1) or a[i] != i) {
                ans++;
            }
        }
        std::cout << ans << '\n';

        memset(a, 0, sizeof(int) * (n + 10));
    }

    return 0;
}

inline int read() {
    int x = 0;
    char ch = getchar();
    while (!isdigit(ch)) {
        ch = getchar();
    }
    while (isdigit(ch)) {
        x = x * 10 + ch - 48;
        ch = getchar();
    }
    return x;
}