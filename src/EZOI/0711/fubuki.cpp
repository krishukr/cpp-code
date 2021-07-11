#include <iostream>

int main() {
    freopen("fubuki.in", "r", stdin);
    freopen("fubuki.out", "w", stdout);

    int n, m, k;
    std::cin >> n >> m >> k;
    if (k) {
        std::cout << k << '\n';
    } else {
        std::cout << 1 << '\n';
    }

    fclose(stdin);
    fclose(stdout);
    return 0;
}