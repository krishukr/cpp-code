#include <cstdio>
#include <iostream>

bool vis[1 << 20];
int ans[1 << 20];

template <typename T>
T read();

int main() {
    std::ios::sync_with_stdio(false);

    int n = read<int>(), x = read<int>(), cnt = 0;

    vis[x] = true;
    for (int i = 1; i < (1 << n); i++) {
        if (!vis[i]) {
            vis[i] = vis[i ^ x] = true;
            ans[++cnt] = i;
        }
    }

    std::cout << cnt << '\n';
    for (int i = cnt; i > 0; i--) {
        ans[i] ^= ans[i - 1];
    }

    for (int i = 1; i <= cnt; i++) {
        std::cout << ans[i] << ' ';
    }

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