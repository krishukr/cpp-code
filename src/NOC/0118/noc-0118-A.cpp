#include <algorithm>
#include <cstdio>
#include <iostream>

const int MAX_N = 100050;

int a[MAX_N], b[MAX_N], s[MAX_N];
int n, len;

template <typename T>
T read();

bool check(int x);

int main() {
    std::ios::sync_with_stdio(false);

    n = read<int>(), len = read<int>();
    for (int i = 1; i <= n; i++) {
        b[i] = a[i] = read<int>();
    }
    std::sort(b + 1, b + n + 1);

    int l = 1, r = n;
    while (l <= r) {
        int mid = (l + r) / 2;
        if (check(b[mid])) {
            l = mid + 1;
        } else {
            r = mid - 1;
        }
    }
    std::cout << b[r] << '\n';

    return 0;
}

bool check(int x) {
    int min = 0x3f3f3f3f;
    for (int i = 1; i <= n; i++) {
        s[i] = s[i - 1] + (a[i] >= x ? 1 : -1);
    }

    for (int i = len; i <= n; i++) {
        min = std::min(min, s[i - len]);
        if (s[i] > min) {
            return true;
        }
    }
    return false;
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