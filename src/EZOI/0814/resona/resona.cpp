#include <cstdio>
#include <cstring>
#include <iostream>

const int MAX_N = 2000050;

int num[MAX_N], vis[MAX_N];

template <typename T>
T read();

int main() {
    freopen("resona.in", "r", stdin);
    freopen("resona.out", "w", stdout);

    int T = read<int>();
    while (T--) {
        memset(num, 0, sizeof(num));
        memset(vis, 0, sizeof(vis));

        int n = read<int>(), m = read<int>(), ans = 0;

        for (int i = 1; i <= n; i++) {
            num[i] = read<int>();
        }

        for (int i = 1; i <= n; i++) {
            for (int j = i; j <= n; j++) {
                memset(vis, 0, sizeof(vis));
                bool flag = true;

                for (int k = i; k <= j; k++) {
                    vis[num[k]]++;
                }
                vis[0] = vis[1];
                for (int k = 1; k <= m; k++) {
                    if (vis[k - 1] != vis[k]) {
                        flag = false;
                        break;
                    }
                }

                if (flag) {
                    ans++;
                }
            }
        }

        std::cout << ans << '\n';
    }

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