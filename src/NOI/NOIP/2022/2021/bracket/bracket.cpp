#include <cstdio>
#include <iostream>

using ll = long long;

constexpr int MAX_N = 505;
constexpr int MOD = 1e9 + 7;

ll f[6][MAX_N][MAX_N];

template <typename T>
T read();

template <typename T>
void read(T& t);

template <typename T, typename... Args>
void read(T& t, Args&... rest);

int main() {
    freopen("bracket.in", "r", stdin);
    freopen("bracket.out", "w", stdout);
    std::ios::sync_with_stdio(false);

    int n, K;
    std::cin >> n >> K;
    std::string s;
    std::cin >> s;

    for (int i = 1; i <= n; i++) {
        f[0][i][i - 1] = 1;
    }
    for (int i = 1; i <= n; i++) {
        for (int l = 1; l <= n - i + 1; l++) {
            const auto r = l + i - 1;
            if (i <= K) {
                f[0][l][r] =
                    f[0][l][r - 1] and (s[r - 1] == '*' or s[r - 1] == '?');
            }
            if (i >= 2) {
                if ((s[l - 1] == '(' or s[l - 1] == '?') and
                    (s[r - 1] == ')' or s[r - 1] == '?')) {
                    f[1][l][r] = (f[0][l + 1][r - 1] + f[2][l + 1][r - 1] +
                                  f[3][l + 1][r - 1] + f[4][l + 1][r - 1]) %
                                 MOD;
                }

                for (int m = l; m < r; m++) {
                    f[2][l][r] += f[3][l][m] * f[0][m + 1][r] % MOD;
                    f[2][l][r] %= MOD;
                    f[3][l][r] +=
                        (f[2][l][m] + f[3][l][m]) * f[1][m + 1][r] % MOD;
                    f[3][l][r] %= MOD;
                    f[4][l][r] +=
                        (f[4][l][m] + f[5][l][m]) * f[1][m + 1][r] % MOD;
                    f[4][l][r] %= MOD;
                    f[5][l][r] += f[4][l][m] * f[0][m + 1][r] % MOD;
                    f[5][l][r] %= MOD;
                }
            }
            f[5][l][r] += f[0][l][r];
            f[5][l][r] %= MOD;
            f[3][l][r] += f[1][l][r];
            f[3][l][r] %= MOD;
        }
    }
    std::cout << f[3][1][n] << '\n';

    std::cout << std::flush;
    fclose(stdin);
    fclose(stdout);
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

template <typename T>
void read(T& t) {
    t = read<T>();
}

template <typename T, typename... Args>
void read(T& t, Args&... rest) {
    t = read<T>();
    read(rest...);
}