#include <cstdio>
#include <iostream>
#include <map>

const int MAX_N = 100050;

int a[MAX_N], b[MAX_N];
std::map<int, int> m;

int cnt;

int id(int x);

template <typename T>
T read();

int main() {
    std::ios::sync_with_stdio(false);

    int n = read<int>(), k = read<int>();

    for (int i = 1; i <= n; i++) {
        int x = read<int>();
        a[i] = id(x);
    }

    int l = 1, r = 0, res = 0, ans = 1;
    while (r <= n) {
        r++;
        if (!b[a[r]]) {
            res++;
        }
        b[a[r]]++;

        while (res > k + 1) {
            b[a[l]]--;
            if (!b[a[l]]) {
                res--;
            }
            l++;
        }

        ans = std::max(ans, b[a[r]]);
    }

    std::cout << ans << '\n';

    return 0;
}

int id(int x) {
    if (!m[x]) {
        m[x] = ++cnt;
    }
    return m[x];
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