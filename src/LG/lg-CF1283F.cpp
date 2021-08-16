#include <cstdio>
#include <iostream>

const int MAX_N = 200050;

int a[MAX_N];
bool vis[MAX_N];

template <typename T>
T read();

int main() {
    std::ios::sync_with_stdio(false);

    int n = read<int>();
    int cnt = n;

    for (int i = 1; i < n; i++) {
        a[i] = read<int>();
    }
    std::cout << a[1] << '\n';
    vis[a[1]] = true;

    for (int i = 1; i < n; i++) {
        while (vis[cnt]) {
            cnt--;
        }

        if (vis[a[i + 1]] or i == n - 1) {
            std::cout << a[i] << ' ' << cnt << '\n';
            vis[cnt] = true;
        } else {
            std::cout << a[i + 1] << ' ' << a[i] << '\n';
            vis[a[i + 1]] = true;
        }
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