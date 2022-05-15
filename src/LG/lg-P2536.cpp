#include <cstdio>
#include <cstring>
#include <iostream>

constexpr int MAX_N = 1050;

bool f[MAX_N][MAX_N];

int main() {
    std::ios::sync_with_stdio(false);

    std::string p;
    int n, ans{};
    std::cin >> p >> n;

    while (n--) {
        std::string t;
        std::cin >> t;

        f[0][0] = true;
        for (int i = 1; p[i - 1] == '*'; i++) {
            f[i][0] = true;
        }
        for (int i = 1; i <= p.length(); i++) {
            for (int j = 1; j <= t.length(); j++) {
                if (p[i - 1] == '?') {
                    f[i][j] = f[i - 1][j - 1];
                } else if (p[i - 1] == '*') {
                    f[i][j] = f[i - 1][j] or f[i - 1][j - 1] or f[i][j - 1];
                } else {
                    f[i][j] = f[i - 1][j - 1] and p[i - 1] == t[j - 1];
                }
            }
        }
        ans += !f[p.length()][t.length()];

        memset(f, 0, sizeof(f));
    }
    std::cout << ans << '\n';

    return 0;
}
