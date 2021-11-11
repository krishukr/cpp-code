#include <cstdio>
#include <iostream>

typedef long long ll;

const int MAX_N = 1050;

int a[MAX_N], num[2];
ll dp[MAX_N];

template <typename T>
T read();

int main() {
    std::ios::sync_with_stdio(false);

    int n = read<int>();
    for (int i = 1; i <= n; i++) {
        a[i] = read<int>();
    }
    a[1] = 0;

    bool flag = true;
    for (int i = 1; i <= n; i++) {
        if (!(i & 1)) {
            num[a[i]]++;
        }
        if (a[i] and a[i + 1]) {
            flag = false;
        }
    }

    if (flag) {
        std::cout << num[0] << '\n' << num[1] << '\n';
        return 0;
    }

    for (int i = 1; i <= n; i++) {
        if (a[i]) {
            dp[i] = 1;
        } else {
            dp[i] = 0x3f3f3f3f3f3f3f3f;
        }
    }
    for (int i = 3; i <= n; i++) {
        if (a[i] and a[i - 1]) {
            for (int j = i - 2; j > 0; j--) {
                dp[j] = std::min(dp[j], dp[j + 1] + dp[j + 2]);
            }
            for (int j = i + 1; j <= n; j++) {
                dp[j] = std::min(dp[j], dp[j - 1] + dp[j - 2]);
            }
        }
    }

    ll ans = 0;
    for (int i = 2; i <= n; i += 2) {
        ans += dp[i];
    }
    std::cout << "0\n" << ans << '\n';

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