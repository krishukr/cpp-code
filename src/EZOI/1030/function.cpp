#include <cstdio>
#include <iostream>

const int MOD = 998244353;

template <typename T>
T read();

int main() {
    freopen("function.in", "r", stdin);
    freopen("function.out", "w", stdout);

    int n = read<int>(), k = read<int>();
    if (k == 1) {
        int ans = 0;
        for (int i = 1; i <= n; i++) {
            ans += i;
            ans %= MOD;
        }
        std::cout << ans << '\n';
    }

    fclose(stdin);
    fclose(stdout);
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