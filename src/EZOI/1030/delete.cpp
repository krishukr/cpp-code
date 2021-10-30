#include <cstdio>
#include <cstring>
#include <iostream>

int main() {
    freopen("delete.in", "r", stdin);
    freopen("delete.out", "w", stdout);

    std::string s;
    std::cin >> s;
    int n = s.length(), ans = 0, sum = 0;

    for (int i = 0; i < n; i++) {
        sum += s[i] - '0';
        if (sum > 9) {
            ans++;
            sum = sum / 10 + sum % 10;
        }
    }

    std::cout << ans + n - 1 << '\n';

    fclose(stdin);
    fclose(stdout);
    return 0;
}