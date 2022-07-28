#include <cstdio>
#include <iostream>

constexpr int MAX_N = 5050;

int f[MAX_N][MAX_N];
bool mp[MAX_N][MAX_N];

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    std::string s;
    std::cin >> s;
    s = std::string(" " + s);
    const auto n = s.length() - 1;
    for (int i = 1; i <= n; i++) {
        f[i][i] = 1;
    }

    for (int k = 1; k <= n; k++) {
        for (int i = 1, j = k; j <= n; i++, j++) {
            mp[i][j] = (s[i] == s[j] and (mp[i + 1][j - 1] or i >= j - 1));
        }
    }

    for (int k = 2; k <= n; k++) {
        for (int i = 1, j = k; j <= n; i++, j++) {
            f[i][j] =
                f[i + 1][j] + f[i][j - 1] - f[i + 1][j - 1] + (int)(mp[i][j]);
        }
    }

    int q;
    std::cin >> q;
    while (q--) {
        int l, r;
        std::cin >> l >> r;
        std::cout << f[l][r] << '\n';
    }

    return 0;
}