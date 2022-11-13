#include <algorithm>
#include <cstdio>
#include <iostream>
#include <string>
#include <unordered_map>
#include <utility>
#include <vector>

std::unordered_map<std::string, int> mp;
std::vector<std::pair<int, std::string>> ans;

int main() {
    std::ios::sync_with_stdio(false);

    int n;
    std::cin >> n;
    for (int i = 1; i <= n; i++) {
        std::string s;
        std::cin >> s;
        mp[s]++;
    }
    for (const auto& i : mp) {
        if (i.second > 2) {
            ans.push_back({-i.second, i.first});
        }
    }

    std::sort(ans.begin(), ans.end());
    std::cout << ans.size() << '\n';
    for (const auto& i : ans) {
        std::cout << i.second << '\n';
    }

    return 0;
}
