#include <algorithm>
#include <cstdio>
#include <cstring>
#include <iostream>
#include <vector>

bool vis[100050];

template <typename T>
T read();

int main() {
    std::ios::sync_with_stdio(false);

    int T = read<int>();
    while (T--) {
        int n = read<int>(), m = read<int>();
        if (m > n / 2) {
            std::cout << n << ' ';
            int s = ((n - m - 1) > 0 ? (n - m - 1) : 0);
            for (int i = s; i > 0; i--) {
                std::cout << i << ' ';
            }
            for (int i = s + 1; i < n; i++) {
                std::cout << i << ' ';
            }
            std::cout << '\n';
            continue;
        }
        memset(vis, 0, sizeof(vis));

        for (int i = 1; i <= m; i++) {
            std::cout << n - i + 1 << ' ';
            vis[n - i + 1] = true;
        }
        for (int i = 1; i <= m; i++) {
            std::cout << i << ' ';
            vis[i] = true;
        }

        for (int i = n; i > 0; i--) {
            if (!vis[i]) {
                std::cout << i << ' ';
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