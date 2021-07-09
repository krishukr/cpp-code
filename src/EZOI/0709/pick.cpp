#include <algorithm>
#include <climits>
#include <cstring>
#include <iostream>

const int MAX_N = 500010;

int a[MAX_N], b[MAX_N], w[MAX_N];
long long c[MAX_N];
long long tot, ans;
int n;

int inline read();

int inline low_bit(int x);

void mod(int pos, long long w);

long long query(int pos);

int main() {
    freopen("pick.in", "r", stdin);
    freopen("pick.out", "w", stdout);

    int T = read();
    while (T--) {
        memset(c, 0, sizeof(c));
        memset(w, 0, sizeof(w));
        tot = ans = 0;
        n = read();
        int cnt = 0;

        for (int i = 1; i <= n; i++) {
            a[i] = read();
            b[i] = a[i];
            tot += a[i];
        }
        std::sort(b + 1, b + n + 1);

        for (int i = 1; i <= n; i++) {
            if (i == 1 or b[i] != b[i - 1]) {
                cnt++;
            }
            w[b[i]] = cnt;
        }

        for (int i = 1; i <= n; i++) {
            long long tmp = query(w[a[i]]);
            mod(w[a[i]], tmp + a[i]);
            ans = std::max(ans, tmp + a[i]);
        }

        std::cout << tot - ans << '\n';
    }

    fclose(stdin);
    fclose(stdout);
    return 0;
}

int inline low_bit(int x) { return x & (-x); }

void mod(int pos, long long w) {
    while (pos <= n) {
        c[pos] = std::max(c[pos], w);
        pos += low_bit(pos);
    }
}

long long query(int pos) {
    long long ans = 0;
    while (pos) {
        ans = std::max(ans, c[pos]);
        pos -= low_bit(pos);
    }
    return ans;
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