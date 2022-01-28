#include <algorithm>
#include <cstdio>
#include <iostream>

typedef long long ll;

const int MAX_N = 1000050;

struct Node {
    int x;
    int y;
} n1[MAX_N], n2[MAX_N];

int cnt1, cnt2;

template <typename T>
T read();

int main() {
    std::ios::sync_with_stdio(false);

    int n = read<int>();
    for (int i = 1; i <= n; i++) {
        int x = read<int>(), y = read<int>();
        if (x < y) {
            n1[++cnt1] = {x, y};
        } else {
            n2[++cnt2] = {x, y};
        }
    }

    std::sort(n1 + 1, n1 + cnt1 + 1,
              [](const Node &a, const Node &b) -> bool { return a.x < b.x; });
    std::sort(n2 + 1, n2 + cnt2 + 1,
              [](const Node &a, const Node &b) -> bool { return a.y > b.y; });

    ll vai = 0, ans = 0;
    for (int i = 1; i <= cnt1; i++) {
        if (n1[i].x > vai) {
            ans += n1[i].x - vai;
            vai = n1[i].y;
        } else {
            vai += n1[i].y - n1[i].x;
        }
    }
    for (int i = 1; i <= cnt2; i++) {
        if (n2[i].x > vai) {
            ans += n2[i].x - vai;
            vai = n2[i].y;
        } else {
            vai += n2[i].y - n2[i].x;
        }
    }
    std::cout << ans << '\n';

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