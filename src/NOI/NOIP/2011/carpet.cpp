#include <cstdio>
#include <iostream>

const int MAX_N = 100050;

struct Node {
    int x1;
    int y1;
    int x2;
    int y2;
} node[MAX_N];

template <typename T>
T read();

int main() {
    freopen("carpet.in", "r", stdin);
    freopen("carpet.out", "w", stdout);

    int n = read<int>(), ans = -1;
    for (int i = 1; i <= n; i++) {
        int x = read<int>(), y = read<int>(), g = read<int>(), k = read<int>();
        node[i] = (Node){x, y, x + g, y + k};
    }
    int qx = read<int>(), qy = read<int>();

    for (int i = 1; i <= n; i++) {
        if (node[i].x1 <= qx and qx <= node[i].x2 and node[i].y1 <= qy and
            qy <= node[i].y2) {
            ans = i;
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