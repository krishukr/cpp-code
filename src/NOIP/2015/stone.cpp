#include <algorithm>
#include <cstdio>
#include <iostream>

const int MAX_N = 100050;

int s[MAX_N];

template <typename T>
T read();

int main() {
    std::ios::sync_with_stdio(false);

    int x = read<int>(), n = read<int>(), m = read<int>();
    for (int i = 1; i <= n; i++) {
        s[i] = read<int>();
    }
    std::sort(s + 1, s + n + 1);

    int l = 1, r = x;
    while (l != r) {
        int mid = (l + r + 1) / 2;
        int a = 0, cnt = 0, i = 1;
        for (i = 1; i <= n; i++) {
            if (x - s[i] < mid) {
                break;
            }
            if (s[i] - a < mid) {
                cnt++;
            } else {
                a = s[i];
            }
        }
        cnt += n - i + 1;
        if (cnt <= m) {
            l = mid;
        } else {
            r = mid - 1;
        }
    }

    std::cout << l << '\n';

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