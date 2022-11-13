#include <algorithm>
#include <cstdio>
#include <cstdlib>
#include <iostream>
#include <string>
#include <unordered_map>

constexpr int MAX_N = 30050;

std::string s[MAX_N];
std::unordered_map<std::string, int> mp;

int n, m, p, q;

void dfs(std::string s);

int main() {
    std::ios::sync_with_stdio(false);

    std::cin >> n >> m >> p >> q;
    for (int i = 1; i <= n; i++) {
        std::cin >> s[i];
        mp[s[i]]++;
    }

    if (p) {
        for (int i = 1; i <= n; i++) {
            std::string ans;
            for (int j = 0; j < m; j++) {
                ans.push_back(s[i][j] == 'Y' ? 'N' : 'Y');
            }
            if (mp[s[i]] == p and mp[ans] == q) {
                if (p == q) {
                    std::cout << std::min(s[i], ans) << '\n';
                } else {
                    std::cout << s[i] << '\n';
                }
                return 0;
            }
        }
    } else if (q) {
        for (int i = 1; i <= n; i++) {
            std::string ans;
            for (int j = 0; j < m; j++) {
                ans.push_back(s[i][j] == 'Y' ? 'N' : 'Y');
            }
            if (mp[ans] == p and mp[s[i]] == q) {
                std::cout << ans << '\n';
                return 0;
            }
        }
    } else {
        dfs("");
    }
    std::cout << -1 << '\n';

    return 0;
}

void dfs(std::string s) {
    if (s.length() == m) {
        std::string rs;
        for (int j = 0; j < m; j++) {
            rs.push_back(s[j] == 'Y' ? 'N' : 'Y');
        }
        if (mp[s] == p and mp[rs] == q) {
            std::cout << s << '\n';
            exit(0);
        }
        return;
    }
    dfs(s + 'N');
    dfs(s + 'Y');
}
