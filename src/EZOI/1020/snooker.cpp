#include <cstdio>
#include <iostream>
#include <vector>

const int MAX_N = 100050;

struct Node {
    char dir;
    int pos;
    int idx;
} q[MAX_N];

char ch[MAX_N];

int ans[MAX_N];

template <typename T>
T read();

int main() {
    freopen("snooker.in", "r", stdin);
    freopen("snooker.out", "w", stdout);

    int n = read<int>();
    for (int i = 1; i <= n; i++) {
        q[i].idx = i;
        q[i].pos = read<int>();
    }

    std::cin >> (ch + 1);
    for (int i = 1; i <= n; i++) {
        q[i].dir = ch[i];
    }

    std::vector<Node> mem;
    for (int i = 1; i <= n; i++) {
        if (q[i].dir == 'R') {
            mem.push_back(q[i]);

        } else {
            if (mem.empty()) {
                ans[q[i].idx] = -1;
            } else {
                ans[q[i].idx] = ans[mem.back().idx] = q[i].pos - mem.back().pos;
                mem.pop_back();
            }
            continue;
        }
    }

    for (int i = 1; i <= n; i++) {
        if (!ans[i]) {
            ans[i] = -1;
        }
        std::cout << ans[i] << ' ';
    }
    std::cout << '\n';

    fclose(stdin);
    fclose(stdout);
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