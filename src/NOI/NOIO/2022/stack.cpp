#include <algorithm>
#include <cstdio>
#include <iostream>
#include <stack>

constexpr int MAX_N = 500050;

struct U {
    int a;
    int b;
    int idx;
} u[MAX_N];

int f[MAX_N], t[MAX_N];
int n, q;

std::stack<U> stk;

bool check(int j);

template <typename T>
T read();

int main() {
    freopen("stack.in", "r", stdin);
    freopen("stack.out", "w", stdout);

    n = read<int>(), q = read<int>();
    for (int i = 1; i <= n; i++) {
        u[i].a = read<int>();
        u[i].idx = i;
    }
    for (int i = 1; i <= n; i++) {
        u[i].b = read<int>();
    }

    for (int j = 2; j <= n; j++) {
        int i = j - 1;
        if (u[i].a != u[j].a and u[i].b > u[j].b) {
            f[j] = 1;
            t[j] = i;
            stk.push(u[i]);
            stk.push(u[j]);
            while (check(j + 1)) {
                j++;
                stk.push(u[j]);
            }
        }
        while (!stk.empty()) {
            stk.pop();
        }
    }

    while (q--) {
        int l = read<int>(), r = read<int>();
        int ans = 0;
        for (int i = l; i <= r; i++) {
            ans += !(f[i] and t[i] >= l);
        }
        std::cout << ans << '\n';
    }

    fclose(stdin);
    fclose(stdout);
    return 0;
}

bool check(int j) {
    if (j > n) {
        return false;
    }
    while (!stk.empty()) {
        auto&& p = stk.top();
        if (p.a != u[j].a and p.b > u[j].b) {
            f[j] = 1;
            t[j] = p.idx;
            return true;
        }
        stk.pop();
    }
    return false;
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