#include <algorithm>
#include <climits>
#include <cstdio>
#include <iostream>
#include <set>

const int MOD = 1000000;

std::set<int> s;
int ans;

void query(int x);

template <typename T>
T read();

int main() {
    std::ios::sync_with_stdio(false);

    int n = read<int>(), crt;
    s.insert(INT_MAX / 2);
    s.insert(INT_MIN / 2);

    for (int i = 1; i <= n; i++) {
        int x = read<int>(), y = read<int>();
        if (s.size() == 2) {
            crt = x;
            s.insert(y);
        } else if (x == crt) {
            s.insert(y);
        } else {
            query(y);
        }
    }

    std::cout << ans << '\n';

    return 0;
}

void query(int x) {
    std::set<int>::iterator l, r;
    l = --s.lower_bound(x);
    r = s.lower_bound(x);

    if (x - *l <= *r - x and *l != (INT_MIN / 2)) {
        ans += x - *l;
        s.erase(l);
    } else {
        ans += *r - x;
        s.erase(r);
    }
    ans %= MOD;
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