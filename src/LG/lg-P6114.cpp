#include <cstdio>
#include <cstring>
#include <iostream>

int main() {
    std::ios::sync_with_stdio(false);

    std::string s;
    std::cin >> s;
    int n = s.length(), ans = 0;

    for (int i = 0; i < n;) {
        int j, k;
        for (j = i, k = i + 1; k < n and s[j] <= s[k]; k++) {
            if (s[j] < s[k]) {
                j = i;
            } else {
                j++;
            }
        }

        while (i <= j) {
            ans ^= i + k - j;
            i += k - j;
        }
    }

    std::cout << ans << '\n';

    return 0;
}