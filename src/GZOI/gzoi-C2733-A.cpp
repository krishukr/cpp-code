#include <bits/stdc++.h>

int main() {
    std::ios::sync_with_stdio(false);
    std::cout << std::fixed << std::setprecision(2);

    int T;
    std::cin >> T;
    while (T--) {
        std::set<std::pair<double, double>> ans;
        double x, y, r;
        std::cin >> x >> y >> r;
        if (r >= std::abs(y)) {
            const auto d = std::sqrt(r * r - y * y);
            ans.insert({x - d, 0});
            ans.insert({x + d, 0});
        }
        if (r >= std::abs(x)) {
            const auto d = std::sqrt(r * r - x * x);
            ans.insert({0, y - d});
            ans.insert({0, y + d});
        }

        std::cout << ans.size() << '\n';
        for (const auto& i : ans) {
            std::cout << i.first << ' ' << i.second << '\n';
        }
    }

    return 0;
}