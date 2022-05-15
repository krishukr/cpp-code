#include <cstdio>
#include <cstring>
#include <iostream>

constexpr int MAX_N = 100050;

char p[MAX_N], t[MAX_N];

bool dfs(int i, int j);

int main() {
    std::ios::sync_with_stdio(false);

    scanf("%s", p + 1);
    const int pl = std::strlen(p + 1);

    int n;
    scanf("%d", &n);
    while (n--) {
        scanf("%s", t + 1);
        const int tl = std::strlen(t + 1);
        std::cout << (dfs(pl, tl) ? "YES" : "NO") << '\n';
    }

    return 0;
}

bool dfs(int i, int j) {
    if (j == 0) {
        if (__builtin_expect((i == 0), 0)) {
            return true;
        }
        for (int k = i; k > 0; k--) {
            if (p[k] != '*') {
                return false;
            }
        }
        return true;
    }
    if (i == 0) {
        return false;
    }

    if (p[i] != '*') {
        if (p[i] == t[j] or p[i] == '?') {
            return dfs(i - 1, j - 1);
        } else {
            return false;
        }

    } else {
        for (int k = j; k >= 0; k--) {
            if (dfs(i - 1, k)) {
                return true;
            }
        }
    }
    return false;
}