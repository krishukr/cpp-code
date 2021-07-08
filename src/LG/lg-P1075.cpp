#include <iostream>

int main() {
    std::ios::sync_with_stdio(false);

    int n;
    std::cin >> n;
    for (int i = 2; i <= n; i++) {
        if (n % i == 0) {
            std::cout << n / i << '\n';
            break;
        }
    }

    return 0;
}