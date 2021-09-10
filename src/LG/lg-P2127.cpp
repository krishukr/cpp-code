#include <algorithm>
#include <cstdio>
#include <iostream>

typedef long long ll;

const int MAX_N = 100050;

ll a[MAX_N], b[MAX_N], p[MAX_N];
bool vis[MAX_N];

ll g_min = 0x7f7f7f7f, siz, sum, min = 0x7f7f7f7f, ans;

void dfs(int x);

template <typename T>
T read();

int main() {
    std::ios::sync_with_stdio(false);

    int n = read<int>();
    for (int i = 1; i <= n; i++) {
        a[i] = read<int>();
        b[i] = a[i];
        g_min = std::min(g_min, a[i]);
    }
    std::sort(b + 1, b + n + 1);

    for (int i = 1; i <= n; i++) {
        p[i] = std::lower_bound(b + 1, b + n + 1, a[i]) - b;
    }

    for (int i = 1; i <= n; i++) {
        if (vis[i]) {
            continue;
        }

        dfs(i);
        ans += std::min(sum + min + g_min * (siz + 1), sum + min * (siz - 2));

        siz = 0, sum = 0, min = 0x7f7f7f7f;
    }

    std::cout << ans << '\n';

    return 0;
}

void dfs(int x) {
    if (vis[x]) {
        return;
    }

    sum += a[x];
    siz++;
    min = std::min(min, a[x]);
    vis[x] = true;

    dfs(p[x]);
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