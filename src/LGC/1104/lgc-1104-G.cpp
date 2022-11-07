#include <cstdio>
#include <iostream>
#include <map>

using ll = long long;

int mp[256];

int main() {
    std::ios::sync_with_stdio(false);

    std::string s;
    std::cin >> s;
    for (int i = 1; i < s.length(); i++) {
        mp[s[i]]++;
    }

    std::string t;
    std::cin >> t;
    ll ans = s.length() * t.length();
    for (int i = 0; i < t.length() - 1; i++) {
        ans -= mp[t[i]];
    }
    std::cout << ans << '\n';

    return 0;
}