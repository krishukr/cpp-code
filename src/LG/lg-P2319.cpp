#include <cstdio>
#include <iostream>
#include <vector>

const int MAX_N = 1050;

int vis[MAX_N], mth[MAX_N], res[MAX_N];

std::vector<int> g[MAX_N];

bool dfs(int x, int t);

template <typename T>
T read();

int main() {
    std::ios::sync_with_stdio(false);

    int n = read<int>(), m = read<int>();
    for (int i = 1; i <= m; i++) {
        int x = read<int>(), y = read<int>();
        x++, y++;
        g[i].push_back(x);
        g[i].push_back(y);
    }

    int ans = 0;
    for (int i = 1; i <= m; i++) {
        if (dfs(i, i)) {
            ans++;
        } else {
            break;
        }
    }

    std::cout << ans << '\n';
    for (int i = 1; i <= ans; i++) {
        std::cout << res[i] - 1 << '\n';
    }

    return 0;
}

bool dfs(int x, int t) {
    if (vis[x] == t) {
        return false;
    }
    vis[x] = t;

    for (auto y : g[x]) {
        if ((!mth[y]) or dfs(mth[y], t)) {
            mth[y] = x;
            res[x] = y;
            return true;
        }
    }
    return false;
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