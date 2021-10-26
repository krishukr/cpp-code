#include <cstdio>
#include <iostream>

const int MAX_N = 505;

int t[MAX_N], a[MAX_N];
int dp[MAX_N][605];
int n;

void build(int x);

void dfs(int x, int t);

template <typename T>
T read();

int main() {
    std::ios::sync_with_stdio(false);

    n = read<int>() - 1;
    build(1);

    dfs(1, t[1]);
    std::cout << dp[1][n] << '\n';

    return 0;
}

void build(int x) {
    t[x] = read<int>() * 2;
    a[x] = read<int>();

    if (!a[x]) {
        build(x * 2);
        build(x * 2 + 1);
    }
}

void dfs(int x, int ti) {
    if (a[x]) {
        for (int i = 1; i <= a[x]; i++) {
            int c = ti + (i * 5);
            if (c > n) {
                break;
            }

            dp[x][c] = dp[x][c - 5] + 1;
        }
    } else {
        int l = x * 2, r = x * 2 + 1;
        dfs(l, ti + t[l]);
        dfs(r, ti + t[r]);

        for (int i = 0; i + ti <= n; i++) {
            for (int j = 0; i + j + ti <= n; j++) {
                dp[x][i + j + ti] =
                    std::max(dp[x][i + j + ti], dp[l][i + ti] + dp[r][j + ti]);
            }
        }
    }
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