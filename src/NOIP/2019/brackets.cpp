#include <cstdio>
#include <iostream>

typedef long long ll;

const int MAX_N = 500050;

ll fa[MAX_N], dp[MAX_N], l[MAX_N], r[MAX_N];

template <typename T>
T read();

int main() {
    // freopen("brackets.in", "r", stdin);
    // freopen("brackets.out", "w", stdout);

    int n = read<int>();
    auto* s = new char[n + 10];
    std::cin >> (s + 1);

    for (int i = 2; i <= n; i++) {
        fa[i] = read<int>();
    }

    ll res = 0;
    for (int i = 1; i <= n; i++) {
        ll faa = fa[i];
        dp[i] = dp[faa];
        l[i] = l[faa];
        if (s[i] == '(') {
            l[i] = i;
        } else if (s[i] == ')' and l[faa]) {
            r[i] = r[fa[l[i]]] + 1;
            l[i] = l[fa[l[i]]];
            dp[i] += r[i];
        }
        res ^= dp[i] * i;
    }

    std::cout << res << '\n';

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