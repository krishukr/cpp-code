#include <algorithm>
#include <cstdio>
#include <iomanip>
#include <iostream>

const int MAX_N = 100050;

struct Node {
    double a;
    double b;
} node[MAX_N];

double sa[MAX_N], sb[MAX_N];

template <typename T>
T read();

int main() {
    // std::ios::sync_with_stdio(false);

    int n = read<int>(), p = read<int>();
    for (int i = 1; i <= n; i++) {
        std::cin >> node[i].a >> node[i].b;
    }
    std::sort(node + 1, node + n + 1, [](const Node &x, const Node &y) -> bool {
        return x.a * y.b > y.a * x.b;
    });
    node[0].a = 1;

    for (int i = 1; i <= n; i++) {
        sa[i] = sa[i - 1] + node[i].a;
        sb[i] = sb[i - 1] + sa[i - 1] * (node[i].b / node[i].a -
                                         node[i - 1].b / node[i - 1].a);
    }

    sb[n + 1] = 100000000000.0;
    double ans = 0.0;
    for (int i = 1; i <= n; i++) {
        if (sb[i + 1] * node[i + 1].a >= node[i + 1].b * p) {
            ans = (node[i].b / node[i].a - sb[i] / p) * p / (sa[i] - p) +
                  node[i].b / node[i].a;
            break;
        }
    }

    if (sa[n] <= p) {
        ans = -1;
    }

    std::cout << std::fixed << std::setprecision(6) << ans << '\n';

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