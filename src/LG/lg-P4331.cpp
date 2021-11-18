#include <cstdio>
#include <iostream>
#include <queue>

#define int long long

const int MAX_N = 1000050;

int a[MAX_N], b[MAX_N];

std::priority_queue<int> q;

template <typename T>
T read();

signed main() {
    std::ios::sync_with_stdio(false);

    int n = read<int>(), ans = 0, res = 0;
    a[1] = b[1] = read<int>() - 1;
    q.push(a[1]);

    for (int i = 2; i <= n; i++) {
        int x = read<int>() - i;
        b[i] = x;
        q.push(x);

        if (q.top() > x) {
            ans += q.top() - x;
            q.pop();
            q.push(x);
        }
        a[i] = q.top();
    }

    for (int i = n - 1; i > 0; i--) {
        a[i] = std::min(a[i], a[i + 1]);
    }

    for (int i = 1; i <= n; i++) {
        res += std::abs(a[i] - b[i]);
    }

    std::cout << res << '\n';
    for (int i = 1; i <= n; i++) {
        std::cout << a[i] + i << ' ';
    }

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