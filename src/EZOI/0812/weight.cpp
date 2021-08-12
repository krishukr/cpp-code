#include <cstdio>
#include <iostream>

typedef long long ll;

const ll MOD = 998244853;

ll ans = 0;

template <typename T>
T read();

int main() {
    freopen("weight.in", "r", stdin);
    freopen("weight.out", "w", stdout);

    int n = read<int>();

    for (int i = 1; i <= n; i++) {
        ans += i * read<int>();
        ans %= MOD;
    }

    std::cout << ans << '\n';

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