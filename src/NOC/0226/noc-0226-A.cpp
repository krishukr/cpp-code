#include <cstdio>
#include <iostream>

typedef long long ll;

const int MAX_N = 5050;
const int dx[] = {0, 0, 0, -1, 1};
const int dy[] = {0, -1, 1, 0, 0};

int a[MAX_N][MAX_N];

template <typename T>
T read();

int main() {
    std::ios::sync_with_stdio(false);

    int n = read<int>(), m = read<int>(), q = read<int>();
    for (int i = 1; i <= q; i++) {
        int x1 = read<int>(), y1 = read<int>();
        int x2 = read<int>(), y2 = read<int>();

        a[x1][y1]++;
        a[x2 + 1][y1]--;
        a[x1][y2 + 1]--;
        a[x2 + 1][y2 + 1]++;
    }

    for (int i = 1; i <= n + 1; i++) {
        for (int j = 1; j <= m + 1; j++) {
            a[i][j] += a[i - 1][j] + a[i][j - 1] - a[i - 1][j - 1];
        }
    }

    ll ans = 0;
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= m; j++) {
            if (a[i][j]) {
                ans += 2;
            }
            for (int k = 1; k <= 4; k++) {
                if (a[i][j] > a[i + dx[k]][j + dy[k]]) {
                    ans += a[i][j] - a[i + dx[k]][j + dy[k]];
                }
            }
        }
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