#include <iostream>

int main() {
    int T;
    std::cin >> T;
    while (T--) {
        int n, x = 0;
        std::cin >> n;
        for (int i = 0; i < n; i++) {
            int tmp;
            std::cin >> tmp;
            x ^= tmp;
        }
        std::cout << (x ? "Yes" : "No") << std::endl;
    }

    return 0;
}