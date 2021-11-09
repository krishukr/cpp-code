#include <cstdio>
#include <iostream>
#include <map>

int main() {
    std::ios::sync_with_stdio(false);

    int T;
    std::cin >> T;
    while (T--) {
        std::map<char, int> mp;
        for (int i = 1; i <= 26; i++) {
            char ch;
            std::cin >> ch;
            mp[ch] = i;
        }

        int ans = 0;
        std::string s;
        std::cin >> s;
        for (int i = 0; i < s.size() - 1; i++) {
            ans += std::abs(mp[s[i]] - mp[s[i + 1]]);
        }
        std::cout << ans << '\n';
    }

    return 0;
}