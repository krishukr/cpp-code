#include <algorithm>
#include <iostream>

const int MAX_N = 100010;

int p[MAX_N], cost[MAX_N];

int main() {
    std::ios::sync_with_stdio(false);

    int n, m;
    long long ans = 0, tmp = 0;
    std::cin >> n >> m;
    for (int i = 1; i <= m; i++) {
        std::cin >> p[i];
    }
    for (int i = 1; i < m; i++) {
        cost[std::max(p[i], p[i + 1])]--;
        cost[std::min(p[i], p[i + 1])]++;
    }

    for (int i = 1; i < n; i++) {
        int a, b, c;
        std::cin >> a >> b >> c;
        tmp += cost[i];
        ans += std::min(a * tmp, b * tmp + c);
    }
    std::cout << ans << "\n";

    return 0;
}