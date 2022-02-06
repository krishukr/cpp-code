#include <cstdio>
#include <iostream>
#include <map>

const int MAX_N = 10000050;

bool vis[MAX_N];

template <typename T>
T read();

int main() {
    // freopen("lgr-102-A.in", "r", stdin);
    // freopen("lgr-102-A.out", "w", stdout);
    std::ios::sync_with_stdio(false);

    int n = read<int>();
    long long ans = 0;

    for (int i = 1; i <= n; i++) {
        int x = read<int>(), t = read<int>();
        if (t > 1) {
            if (!vis[x]) {
                ans += t;
                vis[x] = true;
            }
        }
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