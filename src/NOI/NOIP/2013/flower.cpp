#include <cstdio>
#include <iostream>

const int MAX_N = 100050;

int h[MAX_N];

template <typename T>
T read();

int main() {
    std::ios::sync_with_stdio(false);

    int n = read<int>(), ans = 1;
    bool flag = false;

    for (int i = 1; i <= n; i++) {
        h[i] = read<int>();
    }

    flag = (h[2] >= h[1]);

    for (int i = 1; i <= n; i++) {
        if (flag) {
            if (h[i + 1] < h[i]) {
                ans++;
                flag = false;
            }
        } else {
            if (i == n) {
                ans++;
                break;
            }
            if (h[i + 1] > h[i]) {
                ans++;
                flag = true;
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