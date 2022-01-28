#include <cstdio>
#include <iostream>

typedef long long ll;

template <typename T>
T read();

int main() {
    std::ios::sync_with_stdio(false);

    int T = read<int>();
    while (T--) {
        ll l = read<ll>(), r = read<ll>(), k = read<ll>();
        bool flag = false;

        if (!k) {
            for (ll i = 0; i <= 1; i++) {
                if (i >= l and i <= r) {
                    std::cout << i << ' ';
                    flag = true;
                }
            }
        } else if (k == 1) {
            if (k >= l and k <= r) {
                std::cout << k << ' ';
                flag = true;
            }
        } else {
            for (ll i = 1; i <= r; i *= k) {
                if (i >= l) {
                    std::cout << i << ' ';
                    flag = true;
                }
                if (i > r / k) {
                    break;
                }
            }
        }

        if (!flag) {
            std::cout << "None.";
        }
        std::cout << '\n';
    }

    return 0;
}

template <typename T>
T read() {
    T x = 0, f = 1;
    char ch = getchar();
    while (!isdigit(ch)) {
        if (ch == '-') f = -1;
        ch = getchar();
    }
    while (isdigit(ch)) {
        x = x * 10 + ch - 48;
        ch = getchar();
    }
    return x * f;
}