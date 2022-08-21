#include <cstdio>
#include <cstring>
#include <iostream>

constexpr int MAX_N = 500050;

int t[2][MAX_N];
int cnt;
char s[MAX_N];

int f[2][MAX_N];

void dfs(int x);

int main() {
    std::ios::sync_with_stdio(false);

    std::cin >> (s + 1);
    const int n = std::strlen(s + 1);
    dfs(1);

    for (int i = n; i > 0; i--) {
        f[1][i] = f[0][t[0][i]] + f[0][t[1][i]] + 1;
        f[0][i] = std::max(f[1][t[0][i]] + f[0][t[1][i]],
                           f[1][t[1][i]] + f[0][t[0][i]]);
    }
    std::cout << std::max(f[1][1], f[0][1]) << ' ';

    for (int i = n; i > 0; i--) {
        f[1][i] = f[0][t[0][i]] + f[0][t[1][i]] + 1;
        f[0][i] = std::min(f[1][t[0][i]] + f[0][t[1][i]],
                           f[1][t[1][i]] + f[0][t[0][i]]);
    }
    std::cout << std::min(f[1][1], f[0][1]) << '\n';

    return 0;
}

void dfs(int x) {
    cnt++;
    if (s[x] == '0') {
        return;
    }
    if (s[x] == '1') {
        t[0][x] = x + 1;
        dfs(x + 1);
    }
    if (s[x] == '2') {
        t[0][x] = x + 1;
        dfs(x + 1);
        t[1][x] = cnt + 1;
        dfs(cnt + 1);
    }
}