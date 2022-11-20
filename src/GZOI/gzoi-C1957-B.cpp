#include <cstddef>
#include <cstdio>
#include <cstring>
#include <iostream>
#include <stack>
#include <string>

constexpr int MAX_N = 10000050;

int a[MAX_N];

int main() {
    std::ios::sync_with_stdio(false);

    int T;
    std::cin >> T;
    while (T--) {
        std::string s;
        std::cin >> s;
        std::stack<int> stk;

        int cnt{};
        for (int i = 0; i < s.length(); i++) {
            if (s[i] == 'b') {
                if (!stk.empty()) {
                    a[i + 1]--;
                    a[stk.top()]++;
                    stk.pop();
                    cnt++;
                }
            } else {
                stk.push(i + 1);
            }
        }

        int mx{};
        for (int i = 1; i <= s.length(); i++) {
            a[i] += a[i - 1];
        }
        for (int i = 1; i <= s.length(); i++) {
            mx = std::max(mx, a[i]);
        }
        std::cout << std::min(cnt / 2, cnt - mx) << '\n';
        memset(a, 0, sizeof(a));
    }

    return 0;
}