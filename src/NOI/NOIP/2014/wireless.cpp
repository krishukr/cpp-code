#include <cstdio>
#include <iostream>

int m[250][250];

template <typename T>
T read();

int main() {
    std::ios::sync_with_stdio(false);

    int d = read<int>(), n = read<int>(), ans = 0, cnt = 0;

    for (int i = 1; i <= n; i++) {
        int x = read<int>(), y = read<int>();
        m[x + 20][y + 20] = read<int>();
    }

    for (int i = 0; i <= 128; i++) {
        for (int j = 0; j <= 128; j++) {
            int t = 0;
            for (int k = i - d + 20; k <= i + d + 20; k++) {
                for (int l = j - d + 20; l <= j + d + 20; l++) {
                    t += m[k][l];
                }
            }

            if (t > ans) {
                ans = t;
                cnt = 1;
            } else if (t == ans) {
                cnt++;
            }
        }
    }

    std::cout << cnt << ' ' << ans << '\n';

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