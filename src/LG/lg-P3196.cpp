#include <cstdio>
#include <iostream>

const int MAX_N = 10050;

bool mp[MAX_N][MAX_N];
bool vis[MAX_N];
int tag[MAX_N];

template <typename T>
T read();

int main() {
    std::ios::sync_with_stdio(false);

    int n = read<int>(), m = read<int>();
    for (int i = 1; i <= m; i++) {
        int x = read<int>(), y = read<int>();
        mp[x][y] = mp[y][x] = true;
    }

    for (int i = n; i > 0; i--) {
        int x = 0;
        for (int j = 1; j <= n; j++) {
            if (!vis[j] and (!x or tag[j] > tag[x])) {
                x = j;
            }
        }
        vis[x] = true;

        for (int j = 1; j <= n; j++) {
            if (!vis[j] and mp[x][j]) {
                tag[j]++;
            }
        }
    }

    int ans = 0;
    for (int i = 1; i <= n; i++) {
        ans = std::max(ans, tag[i] + 1);
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