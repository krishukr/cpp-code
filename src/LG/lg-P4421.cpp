#include <cstdio>
#include <cstring>
#include <iostream>
#include <map>

std::map<std::string, int> mp;
std::string s[20050];

template <typename T>
T read();

int main() {
    // std::ios::sync_with_stdio(false);

    int n = read<int>();

    for (int i = 1; i <= n; i++) {
        std::cin >> s[i];
        std::map<std::string, bool> vis;
        int m = s[i].length();

        for (int j = 1; j <= m; j++) {
            for (int k = j; k <= m; k++) {
                std::string sub = s[i].substr(j - 1, k - j + 1);
                if (vis[sub]) {
                    continue;
                }
                vis[sub] = true;
                mp[sub]++;
            }
        }
    }

    int ans = 0;
    for (int i = 1; i <= n; i++) {
        ans += mp[s[i]] - 1;
    }
    std::cout << ans << '\n';

    return 0;
}

template <typename T>
T read() {
    T x = 0, f = 1;
    char ch = getchar();
    while (!isdigit(ch)) {
        if (ch == '-') f = -1;
        ch = getchar();
    }
    while (isdigit(ch)) {
        x = x * 10 + ch - 48;
        ch = getchar();
    }
    return x * f;
}