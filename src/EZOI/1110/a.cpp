#include <algorithm>
#include <cstdio>
#include <iostream>
#include <vector>

const int MAX_N = 400050;

struct Node {
    int l;
    int r;
} node[MAX_N];

bool vis[MAX_N];

template <typename T>
T read();

int main() {
    freopen("a.in", "r", stdin);
    freopen("a.out", "w", stdout);

    int n = read<int>();
    for (int i = 1; i <= n; i++) {
        node[i].l = read<int>();
        node[i].r = read<int>();
    }
    std::sort(node + 1, node + n + 1, [](const Node &a, const Node &b) -> bool {
        return a.r < b.r or (a.r == b.r and a.l < b.l);
    });

    int ans = 0;
    for (int i = 1; i <= n; i++) {
        if (vis[i]) {
            continue;
        }
        for (int j = i + 1; j <= n; j++) {
            if (node[j].r > node[i].l and node[j].l > node[i].r and !vis[j]) {
                vis[j] = true;
                ans++;
                break;
            }
        }
    }

    std::cout << ans << '\n';

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