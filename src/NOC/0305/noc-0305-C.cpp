#include <algorithm>
#include <cstdio>
#include <iostream>

const int MAX_N = 500050;

struct Node {
    int l;
    int r;
    int w;
} node[MAX_N], s[MAX_N];

int fa[MAX_N];

int n;

inline void init(int n);

inline int find(int x);

bool check(int x);

template <typename T>
T read();

int main() {
    std::ios::sync_with_stdio(false);

    n = read<int>();
    int k = read<int>();

    for (int i = 1; i <= k; i++) {
        node[i].l = read<int>();
        node[i].r = read<int>();
        node[i].w = read<int>();
    }

    int l = 1, r = k, mid = (l + r + 1) / 2;
    while (l < r) {
        if (check(mid)) {
            l = mid;
        } else {
            r = mid - 1;
        }
        mid = (l + r + 1) / 2;
    }

    std::cout << mid + 1 << '\n';

    return 0;
}

inline void init(int n) {
    for (int i = 1; i <= n; i++) {
        fa[i] = i;
    }
}

inline int find(int x) { return x == fa[x] ? x : (fa[x] = find(fa[x])); }

bool check(int x) {
    init(n);
    for (int i = 1; i <= x; i++) {
        s[i] = node[i];
    }
    std::sort(s + 1, s + x + 1,
              [](const Node& i, const Node& j) { return i.w > j.w; });

    for (int i = 1; i <= x; i++) {
        int j = i;
        int l = s[i].l, r = s[i].r;

        while (j + 1 <= x and s[j + 1].w == s[i].w) {
            j++;
            l = std::max(l, s[j].l);
            r = std::min(r, s[j].r);
        }

        if (l > find(r)) {
            return false;
        }
        while (l <= r) {
            if (fa[r] == r) {
                fa[r] = find(l - 1);
                r--;
            } else {
                r = find(r);
            }
        }
        i = j;
    }
    return true;
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