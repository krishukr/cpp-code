#include <cstdio>
#include <iostream>

const int MAX_N = 5050;

int po[MAX_N];
int dp[MAX_N][MAX_N];

inline bool check(int l, int r, int m);

template <typename T>
T read();

int main() {
    std::ios::sync_with_stdio(false);

    int n = read<int>(), ans = 0;
    for (int i = 1; i <= n; i++) {
        po[i] = read<int>();
    }

    for (int i = 1; i <= n; i++) {
        dp[i][i] = 1;
        int s = 1, l = i;
        ans ^= 1;

        for (int j = i - 1; j > 0; j--) {
            if (j == i - 1 or check(j, i, l)) {
                s += std::min(dp[j + 1][l], dp[j + 1][l - 1]);
                l = j;
            }

            dp[j][i] = s + std::min(dp[j][l], dp[j][l - 1]);
            ans ^= dp[j][i];
        }
    }

    std::cout << ans << '\n';

    return 0;
}

inline bool check(int l, int r, int x) {
    return (po[r] - po[l]) / (r - l) < (po[r] - po[x]) / (r - x);
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