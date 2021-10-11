#include <cstdio>
#include <iostream>

const int MAX_N = 100050;

int nxt[MAX_N], col[MAX_N], dfn[MAX_N], siz[MAX_N], tim[MAX_N];

template <typename T>
T read();

int main() {
    std::ios::sync_with_stdio(false);

    int n = read<int>();
    for (int i = 1; i <= n; i++) {
        nxt[i] = read<int>();
    }

    for (int i = 1; i <= n; i++) {
        int cnt = 0;
        for (int j = i;; j = nxt[j], cnt++) {
            if (!col[j]) {
                col[j] = i;
                dfn[j] = cnt;
            } else if (col[j] == i) {
                siz[i] = cnt - dfn[j];
                tim[i] = dfn[j];
                std::cout << cnt << '\n';
                break;
            } else {
                siz[i] = siz[col[j]];
                tim[i] = cnt + std::max(tim[col[j]] - dfn[j], 0);
                std::cout << tim[i] + siz[i] << '\n';
                break;
            }
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