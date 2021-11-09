#include <cmath>
#include <cstdio>
#include <cstring>
#include <iostream>

int main() {
    std::ios::sync_with_stdio(false);

    int Q;
    std::cin >> Q;
    while (Q--) {
        int n;
        std::cin >> n;
        std::string s;
        std::cin >> s;

        double ans = 0;
        for (auto i : s) {
            ans += std::log10(std::abs(i - '0'));
        }
        ans += 0.5 * s.length() * (s.length() - 1) * std::log10(n);

        std::cout << (long long)(ans) + 1ll << '\n';
    }

    return 0;
}