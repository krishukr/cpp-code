#include <iostream>

const int MAX_N = 500050;

long long num[MAX_N], diff1[MAX_N], diff2[MAX_N];

inline int read();

int main() {
    std::ios::sync_with_stdio(false);
    freopen("sequence.in", "r", stdin);
    freopen("sequence.out", "w", stdout);

    int n = read(), m = read();
    long long ans = 0;

    while (m--) {
        int l = read(), r = read(), s = read(), e = read();
        int d = (e - s) / (r - l);
        num[l] += s;
        num[l + 1] += d - s;
        num[r + 1] += -d - e;
        num[r + 2] += e;
    }
    for (int i = 1; i <= n; i++) {
        diff1[i] = diff1[i - 1] + num[i];
        diff2[i] = diff2[i - 1] + diff1[i];
        ans ^= diff2[i];
    }

    std::cout << ans << '\n';

    fclose(stdin);
    fclose(stdout);
    return 0;
}

inline int read() {
    int x = 0, f = 1;
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