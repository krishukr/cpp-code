#include <algorithm>
#include <cstdio>
#include <iostream>

int w[1000050];

template <typename T>
T read();

int main() {
    std::ios::sync_with_stdio(false);

    int n = read<int>(), ans = 0;
    for (int i = 1; i <= n; i++) {
        w[i] = read<int>();
    }

    std::sort(w + 1, w + n + 1);
    for (int i = 1; i <= n; i++) {
        ans = std::max(ans, w[i] - ans);
    }

    std::cout << ans << '\n';

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