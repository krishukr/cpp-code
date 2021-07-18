#include <algorithm>
#include <climits>
#include <cstdio>
#include <iostream>
#include <set>

template <typename T>
T read();

std::set<int> s;
std::set<int>::iterator k, a;

int main() {
    std::ios::sync_with_stdio(false);

    int n = read<int>(), ans = 0;
    s.insert(INT_MAX / 2);
    s.insert(INT_MIN / 2);

    for (int i = 1; i <= n; i++) {
        int x = read<int>();
        if (s.size() == 2) {
            ans += x;
            s.insert(x);
        } else {
            k = s.lower_bound(x);
            if (*k != x) {
                a = k;
                a--;
                ans += std::min(std::abs(*a - x), std::abs(*k - x));
                s.insert(x);
            }
        }
    }

    std::cout << ans << '\n';

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