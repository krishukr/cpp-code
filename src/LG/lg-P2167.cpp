#include <cstdio>
#include <iostream>
#include <memory>
#include <string>

constexpr int MAX_N = 16;
constexpr int MAX_M = 55;
constexpr int MOD = 1000003;

class Solution {
    int f[MAX_M][(1 << MAX_N) + 5];
    int m[MAX_M][MAX_M];
    std::string s[MAX_N];

   public:
    Solution() = default;
    ~Solution() = default;

    void solve();
};

int main() {
    std::ios::sync_with_stdio(false);

    int T;
    std::cin >> T;
    while (T--) {
        auto solution = std::make_unique<Solution>();
        solution->solve();
    }

    return 0;
}

void Solution::solve() {
    int n, k;
    std::cin >> n >> k;
    for (int i = 1; i <= n; i++) {
        std::cin >> s[i];
    }
    const auto l = s[1].length();

    for (int i = 0; i < l; i++) {
        for (char c = 'a'; c <= 'z'; c++) {
            for (int j = 1; j <= n; j++) {
                if (s[j][i] != '?' and s[j][i] != c) {
                    continue;
                }
                m[i][c - 'a'] |= (1 << (j - 1));
            }
        }
    }

    f[0][(1 << n) - 1] = 1;
    for (int i = 0; i < l; i++) {
        for (int j = 0; j <= (1 << n) - 1; j++) {
            if (!f[i][j]) {
                continue;
            }
            for (char c = 'a'; c <= 'z'; c++) {
                f[i + 1][m[i][c - 'a'] & j] += f[i][j];
                f[i + 1][m[i][c - 'a'] & j] %= MOD;
            }
        }
    }

    int ans{};
    for (int i = 0; i <= (1 << n) - 1; i++) {
        int t{};
        for (int j = 1; j <= (1 << n) - 1; j <<= 1) {
            t += ((i & j) != 0);
        }
        if (t == k) {
            ans += f[l][i];
            ans %= MOD;
        }
    }
    std::cout << ans << '\n';
}