#include <cstdio>
#include <iostream>

#define int long long

const int MAX_N = 105;

int a[MAX_N];
int n, m;

bool check(int x);

template <typename T>
T read();

signed main() {
    std::ios::sync_with_stdio(false);

    n = read<int>(), m = read<int>();
    for (int i = 1; i <= n; i++) {
        a[i] = read<int>();
    }

    int l = 0, r = 1e9;
    while (l + 1 < r) {
        int mid = (l + r) / 2;
        if (check(mid)) {
            l = mid;
        } else {
            r = mid;
        }
    }

    std::cout << l << '\n';

    return 0;
}

bool check(int x) {
    int k = 0;
    for (int i = 1; i <= n; i++) {
        k += std::max(0ll, x - a[i]);
    }

    if (k <= std::min(x, m)) {
        return true;
    } else {
        return false;
    }
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