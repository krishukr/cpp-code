#include <cmath>
#include <cstdio>
#include <iostream>
#include <vector>

template <typename T>
T read();

int main() {
    std::ios::sync_with_stdio(false);

    int n = read<int>(), k = read<int>();

    if (n < 2) {
        std::cout << k << '\n';
        for (int i = 1; i <= k; i++) {
            std::cout << 1 << ' ';
        }
        return 0;
    }

    std::vector<int> pri;
    int s = 0, m = n;
    if (n == 2) {
        pri.push_back(2);
        s += 2;
    } else {
        for (int i = 2; i <= std::sqrt(m); i++) {
            while (m != i) {
                if (!(m % i)) {
                    pri.push_back(i);
                    s += i;
                    m /= i;
                } else {
                    break;
                }
            }
        }
        if (m) {
            pri.push_back(m);
            s += m;
        }
    }

    if (s > k) {
        std::cout << -1 << '\n';
    } else {
        int cnt = pri.size() + k - s;
        std::cout << cnt << '\n';
        for (auto i : pri) {
            std::cout << i << ' ';
        }
        for (int i = 1; i <= k - s; i++) {
            std::cout << 1 << ' ';
        }
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