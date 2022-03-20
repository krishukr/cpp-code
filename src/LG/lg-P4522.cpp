#include <cstdio>
#include <iostream>

constexpr int MAX_N = 5050;

int s[MAX_N][MAX_N];
bool a[MAX_N];
bool r[MAX_N][MAX_N];

template <typename T>
T read();

int main() {
    std::ios::sync_with_stdio(false);

    int n = read<int>(), m = read<int>(), k = read<int>();
    for (int i = 1; i <= n; i++) {
        a[i] = read<int>();
    }

    for (int i = 1; i <= m; i++) {
        for (int j = 1; j <= n; j++) {
            int x = j % n + 1, l = std::max(1, i - k);
            int t = s[i - 1][x] - s[l - 1][x];

            if (a[j] != a[x]) {
                r[i][j] = t;
            } else {
                r[i][j] = (t != i - l);
            }

            s[i][j] = s[i - 1][j] + !r[i][j];
        }
    }

    for (int i = 1; i <= n; i++) {
        std::cout << (int)(!(r[m][i] ^ a[i])) << ' ';
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