#include <cstdio>
#include <iostream>

typedef long long ll;

const int MAX_N = 4000050;

ll a[MAX_N];
int l[MAX_N], r[MAX_N];

template <typename T>
T read();

int main() {
    std::ios::sync_with_stdio(false);

    int n = read<int>();
    for (int i = 1; i <= n; i++) {
        a[i] = read<ll>();
    }

    for (int i = 1; i <= n; i++) {
        l[i] = i;
        while (l[i] > 1 and !(a[l[i] - 1] % a[i])) {
            l[i] = l[l[i] - 1];
        }
    }
    for (int i = n; i > 0; i--) {
        r[i] = i;
        while (r[i] < n and !(a[r[i] + 1] % a[i])) {
            r[i] = r[r[i] + 1];
        }
    }

    int ans = 0;
    for (int i = 1; i <= n; i++) {
        ans = std::max(ans, r[i] - l[i] + 1);
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