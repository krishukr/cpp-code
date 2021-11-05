#include <algorithm>
#include <cstdio>
#include <iostream>
#include <vector>

const int MAX_N = 100050;

struct Node {
    int x;
    int y;
} node[MAX_N];

std::vector<int> stk;

template <typename T>
T read();

int main() {
    std::ios::sync_with_stdio(false);

    int n = read<int>();
    for (int i = 1; i <= n; i++) {
        node[i].x = read<int>();
        node[i].y = read<int>();
    }

    std::sort(node + 1, node + n + 1,
              [](const Node &a, const Node &b) -> bool { return a.x < b.x; });

    for (int i = 1; i <= n; i++) {
        if (stk.empty() or node[i].y <= stk.back()) {
            stk.push_back(node[i].y);
        } else {
            *std::lower_bound(stk.begin(), stk.end(), node[i].y,
                              [](const int &a, const int &b) -> bool {
                                  return a >= b;
                              }) = node[i].y;
        }
    }

    std::cout << stk.size() << '\n';

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