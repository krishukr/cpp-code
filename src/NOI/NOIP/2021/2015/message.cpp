#include <climits>
#include <cstdio>
#include <iostream>

const int MAX_N = 200050;

int fa[MAX_N];
int ans = INT_MAX, cnt;

int find(int x);

template <typename T>
T read();

int main() {
    std::ios::sync_with_stdio(false);

    int n = read<int>();
    for (int i = 1; i <= n; i++) {
        fa[i] = i;
    }

    for (int i = 1; i <= n; i++) {
        int x = read<int>();
        cnt = 0;

        if (find(x) == i) {
            ans = std::min(ans, cnt);
        } else {
            fa[i] = x;
        }
    }

    std::cout << ans << '\n';

    return 0;
}

int find(int x) {
    cnt++;
    if (x == fa[x]) {
        return x;
    } else {
        return find(fa[x]);
    }
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