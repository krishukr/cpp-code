#include <cstdio>
#include <iostream>

typedef unsigned long long ull;

int main() {
    // freopen("code.in", "r", stdin);
    // freopen("code.out", "w", stdout);

    int n;
    ull k;
    std::cin >> n >> k;

    k ^= (k / 2);
    while (n--) {
        std::cout << (k >> n & 1);
    }

    fclose(stdin);
    fclose(stdout);
    return 0;
}