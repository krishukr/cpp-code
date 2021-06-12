#include <cmath>
#include <cstring>
#include <iomanip>
#include <iostream>

float d[20][20], x[20], y[20], dp[20][100000];
int n;

float dis(int x, int y);

void init();

int main() {
    std::ios::sync_with_stdio(false);

    std::cin >> n;
    for (int i = 1; i <= n; i++) {
        std::cin >> x[i] >> y[i];
    }
    init();
    float ans = dp[0][0];
    for (int i = 1; i <= n; i++) {
        ans = std::min(ans, dp[i][(1 << n) - 1]);
    }
    std::cout << std::fixed << std::setprecision(2) << ans << '\n';

    return 0;
}

float dis(int u, int v) {
    return sqrt((x[u] - x[v]) * (x[u] - x[v]) + (y[u] - y[v]) * (y[u] - y[v]));
}

void init() {
    memset(dp, 127, sizeof(dp));
    for (int i = 0; i <= n; i++) {
        for (int j = i + 1; j <= n; j++) {
            d[i][j] = d[j][i] = dis(i, j);
        }
    }
    for (int i = 1; i <= n; i++) {
        dp[i][1 << (i - 1)] = d[0][i];
    }
    for (int i = 1; i <= (1 << n); i++) {
        for (int j = 1; j <= n; j++) {
            if ((i & (1 << (j - 1))) == 0) {
                continue;
            }
            for (int k = 1; k <= n; k++) {
                if (j == k) {
                    continue;
                }
                if ((i & (1 << (k - 1))) == 0) {
                    continue;
                }
                dp[j][i] =
                    std::min(dp[j][i], dp[k][i - (1 << (j - 1))] + d[j][k]);
            }
        }
    }
}