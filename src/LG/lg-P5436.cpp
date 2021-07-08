#include <iostream>

int main() {
    std::ios::sync_with_stdio(false);

    int T;
    std::cin >> T;
    while (T--) {
        unsigned long long n;
        std::cin >> n;
        if (n == 1) {
            std::cout << 1 << '\n';
        } else {
            std::cout << n * (n - 1) << '\n';
        }
    }

    return 0;
}