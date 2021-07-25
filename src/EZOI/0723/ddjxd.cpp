#include <cstdio>
#include <cstring>
#include <iostream>

const int MAX_N = 500050;

int n, a, b, ans;

bool vis[MAX_N];
int cnt;

template <typename T>
T read();

void dfs(int x, int w);

int main() {
    freopen("ddjxd.in", "r", stdin);
    freopen("ddjxd.out", "w", stdout);

    n = read<int>(), a = read<int>(), b = read<int>();

    if (n <= MAX_N) {
        for (int i = 0; i <= n; i++) {
            cnt = 0;
            memset(vis, 0, sizeof(vis));

            dfs(0, i);
            ans += cnt;
        }

        std::cout << ans << '\n';
    } else {
        std::cout << "FUCK\n";
    }

    fclose(stdin);
    fclose(stdout);
    return 0;
}

void dfs(int x, int w) {
    if (x < 0 or x > w or vis[x]) {
        return;
    }
    vis[x] = true;
    cnt++;
    dfs(x + a, w);
    dfs(x - b, w);
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