#include <algorithm>
#include <cstdio>
#include <iostream>

typedef long long ll;

const int MAX_N = 100050;

int a[MAX_N];
ll ans;

template <typename T>
T read();

int main() {
    freopen("memset.in", "r", stdin);
    freopen("memset.out", "w", stdout);

    int n = read<int>();
    for (int i = 1; i <= n; i++) {
        a[i] = read<int>();
        ans += 1ll * a[i] * (n - a[i] + 1);
    }

    for (int i = 1; i < n; i++) {
        ans -=
            1ll * std::min(a[i], a[i + 1]) * (n - std::max(a[i], a[i + 1]) + 1);
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