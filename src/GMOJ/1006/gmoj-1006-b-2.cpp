#include <cstdio>
#include <iostream>

const int MAX_N = 260;

int c[MAX_N][MAX_N][MAX_N];
int g;

bool check(int x);

template <typename T>
T read();

int main() {
    std::ios::sync_with_stdio(false);

    int n = read<int>();
    g = read<int>();

    for (int i = 1; i <= n; i++) {
        int x = read<int>(), y = read<int>(), z = read<int>();
        x++, y++, z++;
        c[x][y][z]++;
    }

    for (int i = 1; i < MAX_N; i++) {
        for (int j = 1; j < MAX_N; j++) {
            for (int k = 1; k < MAX_N; k++) {
                c[i][j][k] += c[i - 1][j][k] + c[i][j - 1][k] + c[i][j][k - 1];

                c[i][j][k] -= c[i - 1][j - 1][k] + c[i - 1][j][k - 1] +
                              c[i][j - 1][k - 1];

                c[i][j][k] += c[i - 1][j - 1][k - 1];
            }
        }
    }

    int l = 0, r = MAX_N - 1, ans;
    while (l <= r) {
        int mid = (l + r) / 2;
        if (check(mid)) {
            ans = mid;
            r = mid - 1;
        } else {
            l = mid + 1;
        }
    }

    std::cout << ans << '\n';

    return 0;
}

bool check(int x) {
    int res = -1;
    for (int i = x + 1; i < MAX_N; i++) {
        for (int j = x + 1; j < MAX_N; j++) {
            for (int k = x + 1; k < MAX_N; k++) {
                int t = c[i][j][k];

                t -= c[i - x - 1][j][k] + c[i][j - x - 1][k] +
                     c[i][j][k - x - 1];
                t += c[i - x - 1][j - x - 1][k] + c[i - x - 1][j][k - x - 1] +
                     c[i][j - x - 1][k - x - 1];
                t -= c[i - x - 1][j - x - 1][k - x - 1];

                res = std::max(res, t);
            }
        }
    }
    return res >= g;
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