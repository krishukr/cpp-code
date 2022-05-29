#include <cstdio>
#include <cstring>
#include <iostream>

const int MAX_N = 200050;

int dir[MAX_N];

std::string s[MAX_N];

template <typename T>
T read();

int main() {
    // std::ios::sync_with_stdio(false);
    freopen("toy.in", "r", stdin);
    freopen("toy.out", "w", stdout);

    int n = read<int>(), m = read<int>(), ans = 1;

    for (int i = 1; i <= n; i++) {
        dir[i] = read<int>();
        std::cin >> s[i];
    }

    for (int i = 1; i <= m; i++) {
        int x = read<int>(), y = read<int>();

        ans += (x ^ dir[ans] ? y : n - y);
        ans %= n;
        ans = (!ans ? n : ans);
    }

    std::cout << s[ans] << '\n';

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