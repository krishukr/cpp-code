#include <cstdio>
#include <iostream>

typedef long long ll;

const int MAX_N = 2005;

int a[MAX_N][MAX_N];
int ls[MAX_N][MAX_N], us[MAX_N][MAX_N], rs[MAX_N][MAX_N];
ll s[MAX_N][MAX_N];

inline ll calc(int x1, int y1, int x2, int y2);

template <typename T>
T read();

int main() {
    std::ios::sync_with_stdio(false);

    int k = read<int>(), n = read<int>();

    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= n; j++) {
            a[i][j] = read<int>();

            if (a[i][j] >= k and a[i][j] <= 2 * k) {
                std::cout << j << ' ' << i << ' ' << j << ' ' << i << '\n';
                return 0;
            }
        }
    }

    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= n; j++) {
            s[i][j] = s[i][j - 1] + s[i - 1][j] - s[i - 1][j - 1] + a[i][j];
        }
    }

    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= n; j++) {
            if (a[i][j] < k) {
                us[i][j] = us[i - 1][j] + 1;
                ls[i][j] = ls[i][j - 1] + 1;
            }
        }

        for (int j = n; j > 0; j--) {
            if (a[i][j] < k) {
                rs[i][j] = rs[i][j + 1] + 1;
            }
        }

        for (int j = 1; j <= n; j++) {
            if (us[i][j] > 1) {
                ls[i][j] = std::min(ls[i][j], ls[i - 1][j]);
            }
        }

        for (int j = n; j > 0; j--) {
            if (us[i][j] > 1) {
                rs[i][j] = std::min(rs[i][j], rs[i - 1][j]);
            }
        }
    }

    int l = 0, r = 0, u = 0, d = 0;
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= n; j++) {
            if (a[i][j] < k and calc(i - us[i][j] + 1, j - ls[i][j] + 1, i,
                                     j + rs[i][j] - 1) >= k) {
                l = j - ls[i][j] + 1;
                r = j + rs[i][j] - 1;
                u = i - us[i][j] + 1;
                d = i;
                break;
            }
        }
    }

    if (l == 0) {
        std::cout << "NIE\n";
        return 0;
    }

    while (calc(u, l, d, r) > 2 * k) {
        if (d > u) {
            if (calc(u, l, d - 1, r) < k) {
                u = d;
            } else {
                d--;
            }
        } else {
            r--;
        }
    }

    std::cout << l << ' ' << u << ' ' << r << ' ' << d;

    return 0;
}

inline ll calc(int x1, int y1, int x2, int y2) {
    return s[x2][y2] - s[x1 - 1][y2] - s[x2][y1 - 1] + s[x1 - 1][y1 - 1];
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