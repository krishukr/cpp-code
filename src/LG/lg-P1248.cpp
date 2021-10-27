#include <algorithm>
#include <cstdio>
#include <iostream>

const int MAX_N = 2050;

struct Node {
    int w;
    int idx;
    bool flag;
} node[MAX_N];

int a[MAX_N], b[MAX_N], res[MAX_N];
bool vis[MAX_N];

template <typename T>
T read();

int main() {
    std::ios::sync_with_stdio(false);

    int n = read<int>();

    for (int i = 1; i <= n; i++) {
        a[i] = read<int>();
        node[i] = (Node){a[i], i, true};
    }
    for (int i = 1; i <= n; i++) {
        b[i] = read<int>();
        node[i + n] = (Node){b[i], i, false};
    }
    std::sort(node + 1, node + n + n + 1,
              [](const Node &a, const Node &b) -> bool { return a.w < b.w; });

    int l = 1, r = n;
    for (int i = 1; i <= n + n; i++) {
        if (vis[node[i].idx]) {
            continue;
        }
        vis[node[i].idx] = true;

        if (node[i].flag) {
            res[l++] = node[i].idx;
        } else {
            res[r--] = node[i].idx;
        }
        if (l > r) {
            break;
        }
    }

    int ta = 0, tb = 0;
    std::for_each(res + 1, res + n + 1, [&](const int &i) {
        ta += a[i];
        tb = std::max(tb, ta);
        tb += b[i];
    });

    std::cout << tb << '\n';
    std::for_each(res + 1, res + n + 1,
                  [](const int &i) { std::cout << i << ' '; });
    std::cout << '\n';

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