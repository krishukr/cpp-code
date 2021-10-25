#include <algorithm>
#include <cstdio>
#include <cstring>
#include <iostream>

typedef long long ll;

const int MAX_N = 100050;

ll tot;

struct Node {
    std::string t;
    ll s;
    ll h;

    bool operator<(const Node &n) const { return s * n.h > n.s * h; }

    std::string operator()() const { return t; }

    void calc() {
        for (auto i : t) {
            if (i == 's') {
                s++;
            }
            if (i == 'h') {
                h++;
                tot++;
            }
        }
    }
} q[MAX_N];

template <typename T>
T read();

int main() {
    int n = read<int>();
    for (int i = 1; i <= n; i++) {
        std::cin >> q[i].t;
        q[i].calc();
    }

    std::sort(q + 1, q + n + 1);
    std::string r;
    for (int i = 1; i <= n; i++) {
        r += q[i]();
    }

    ll ans = 0;
    for (auto i : r) {
        if (i == 's') {
            ans += tot;
        }
        if (i == 'h') {
            tot--;
        }
    }

    std::cout << ans << '\n';
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