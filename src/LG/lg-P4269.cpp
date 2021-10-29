#include <algorithm>
#include <cstdio>
#include <iostream>

const int MAX_N = 100050;

struct Blk {
    int dep;
    int idx;
} f[MAX_N];

struct Bot {
    int dep;
    int len;
    int idx;
} s[MAX_N];

int lst[MAX_N], nxt[MAX_N];
bool ans[MAX_N];

template <typename T>
T read();

int main() {
    std::ios::sync_with_stdio(false);

    int n = read<int>(), b = read<int>();
    for (int i = 1; i <= n; i++) {
        f[i].dep = read<int>();
        f[i].idx = i;
    }
    for (int i = 1; i <= b; i++) {
        s[i].dep = read<int>();
        s[i].len = read<int>();
        s[i].idx = i;
    }

    std::sort(f + 1, f + n + 1,
              [](const Blk &x, const Blk &y) -> bool { return x.dep > y.dep; });
    std::sort(s + 1, s + n + 1,
              [](const Bot &x, const Bot &y) -> bool { return x.dep > y.dep; });

    for (int i = 1; i <= n; i++) {
        lst[i] = i - 1;
        nxt[i] = i + 1;
    }

    int j = 1, m = 0;
    for (int i = 1; i <= n; i++) {
        while (j <= n and f[j].dep > s[i].dep) {
            lst[nxt[f[j].idx]] = lst[f[j].idx];
            nxt[lst[f[j].idx]] = nxt[f[j].idx];

            m = std::max(m, nxt[f[j].idx] - lst[f[j].idx]);
            j++;
        }
        ans[s[i].idx] = s[i].len >= m;
    }

    for (int i = 1; i <= b; i++) {
        std::cout << (int)(ans[i]) << '\n';
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