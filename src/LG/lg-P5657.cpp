#include <iostream>

int main() {
    std::ios::sync_with_stdio(false);

    int n;
    unsigned long long k;
    std::cin >> n >> k;

    k ^= k / 2;
    while (~--n) {
        std::cout << (k >> n & 1);
    }

    return 0;
}