#include <algorithm>
#include <cstdio>
#include <iostream>
#include <queue>

const int MAX_N = 100050;

int w[MAX_N], ans[MAX_N];

std::pair<int, int> p[MAX_N];
std::priority_queue<int> q;

template <typename T>
T read();

int main() {
    std::ios::sync_with_stdio(false);

    int n = read<int>(), m = read<int>(), cnt = 0, res = 0;
    for (int i = 1; i <= n; i++) {
        w[i] = read<int>();
    }

    for (int i = 1; i <= m; i++) {
        p[i].first = read<int>();
        p[i].second = read<int>();
    }

    std::sort(p + 1, p + m + 1);
    p[m + 1].first = 0x3f3f3f3f;

    for (int i = 1; i <= n; i++) {
        while (p[cnt + 1].first <= i) {
            q.push(p[++cnt].second);
            ans[p[cnt].second]++;
        }
        while (q.size() > w[i] + res) {
            ans[q.top()]--;
            q.pop();
        }
        res += ans[i];
    }

    std::cout << res << '\n';

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