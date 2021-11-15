#include <cstdio>
#include <functional>
#include <iostream>
#include <map>
#include <vector>

const int MAX_N = 50;
const int MAX_M = 1 << 21;

int a[MAX_N];
bool vis[MAX_M];
std::map<int, int> mp;
std::vector<int> r[MAX_M];
int idx;

template <typename T>
T read();

int main() {
    std::ios::sync_with_stdio(false);

    int n = read<int>();
    int m = n / 2;
    for (int i = 1; i <= n; i++) {
        a[i] = read<int>();
    }

    std::function<void(int, int, int)> dfs = [&](int d, int s, int x) -> void {
        if (d > m) {
            if (!mp.count(s)) {
                mp[s] = ++idx;
            }
            r[mp[s]].push_back(x);
            return;
        }

        dfs(d + 1, s, x);
        dfs(d + 1, s + a[d], x + (1 << (d - 1)));
        dfs(d + 1, s - a[d], x + (1 << (d - 1)));
    };
    dfs(1, 0, 0);

    dfs = [&](int d, int s, int x) -> void {
        if (d > n) {
            if (mp.count(s)) {
                int y = mp[s];
                for (auto i : r[y]) {
                    vis[i + x] = true;
                }
            }
            return;
        }

        dfs(d + 1, s, x);
        dfs(d + 1, s + a[d], x + (1 << (d - 1)));
        dfs(d + 1, s - a[d], x + (1 << (d - 1)));
    };
    dfs(m + 1, 0, 0);

    int ans = 0;
    for (int i = 1; i <= (1 << n); i++) {
        ans += vis[i];
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