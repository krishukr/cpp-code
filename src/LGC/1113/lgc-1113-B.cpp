#include <climits>
#include <cstdio>
#include <iostream>
#include <string>

using ll = long long;

constexpr int MAX_N = 500050;

bool vis[MAX_N];

int main() {
    std::ios::sync_with_stdio(false);

    ll n, k;
    std::cin >> n >> k;
    std::string s, ans;
    std::cin >> s;
    if (k == 0) {
        std::cout << s << '\n';
        return 0;
    }

    ll m{LLONG_MAX}, c{};
    for (int h = 0; h <= 26 and k > 0; h++) {
        ll p{};
        for (int i = 0; i < n and k > 0; i++) {
            if (vis[i]) {
                p++;
                continue;
            }
            if (k >= m - c) {
                ans.push_back(s[m]);
                vis[m] = true;
                for (int j = 0; j < n; j++) {
                    if (vis[j]) {
                        continue;
                    }
                    ans.push_back(s[j]);
                }
                std::cout << ans << '\n';
                return 0;
            }
            if (s[i] - 'a' == h) {
                if (k >= i - p) {
                    k -= i - p;
                    ans.push_back(s[i]);
                    vis[i] = true;
                    c++;
                    p++;
                } else {
                    if (m > i) {
                        m = i;
                        c = p;
                    }
                    break;
                }
            }
        }
    }

    for (int i = 0; i < n; i++) {
        if (vis[i]) {
            continue;
        }
        ans.push_back(s[i]);
    }
    std::cout << ans << '\n';

    return 0;
}
