#include <cstdio>
#include <iostream>

int main() {
    std::ios::sync_with_stdio(false);

    int l = 1, r;
    std::cin >> r;

    while (true) {
        printf("? %d %d\n", l, r);
        std::fflush(stdout);

        int x, op;
        std::cin >> x >> op;
        int mid = (l + r) / 2;
        switch (op) {
            case 0:
                l = x + 1;
                break;
            case 1:
                printf("! %d\n", x);
                std::fflush(stdout);
                return 0;
            case 2:
                r = x - 1;
                break;
            default:
                throw std::runtime_error("Invaild Operation!");
        }

        if (l == r) {
            printf("! %d\n", l);
            std::fflush(stdout);
            return 0;
        }
    }

    return 0;
}