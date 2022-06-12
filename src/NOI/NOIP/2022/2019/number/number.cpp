#include <cstdio>
#include <iostream>

int main() {
    freopen("number.in", "r", stdin);
    freopen("number.out", "w", stdout);
    std::ios::sync_with_stdio(false);

    int ans{};
    for (int i = 1; i <= 8; i++) {
        char ch = getchar();
        while (ch != '0' and ch != '1') {
            ch = getchar();
        }
        ans += (ch == '1');
    }
    std::cout << ans << '\n';

    std::cout << std::flush;
    fclose(stdin);
    fclose(stdout);
    return 0;
}