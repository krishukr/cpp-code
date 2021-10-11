#include <cstdio>
#include <cstring>
#include <iostream>

#define int long long

const int MAX_N = 2000050;
const int MOD = 19930726;

std::string d, s;
int re[MAX_N], cnt[MAX_N];
int n, nn, k;

void init();

void manacher();

int quick_pow(int a, int b);

signed main() {
    std::ios::sync_with_stdio(false);

    std::cin >> nn >> k >> s;
    int sum = 0, ans = 1;
    n = nn;
    init();
    manacher();

    for (int i = nn; i > 0; i--) {
        if (i % 2) {
            sum += cnt[i];
            if (k >= sum) {
                ans *= quick_pow(i, sum);
                ans %= MOD;
                k -= sum;
            } else {
                ans *= quick_pow(i, k);
                ans %= MOD;
                k -= sum;
                break;
            }
        } else {
            continue;
        }
    }

    if (k > 0) {
        std::cout << -1 << '\n';
    } else {
        std::cout << ans << '\n';
    }

    return 0;
}

void init() {
    d.resize(2 * n + 10);
    d[0] = d[1] = 'A';
    for (int i = 0; i < n; i++) {
        d[i * 2 + 2] = s[i];
        d[i * 2 + 3] = 'A';
    }
    n = 2 * n + 2;
    d[n] = 0;
}

void manacher() {
    int r = 0, mid = 0;
    for (int l = 1; l < n; l++) {
        if (l < r) {
            re[l] = std::min(re[mid * 2 - l], re[mid] + mid - l);
        } else {
            re[l] = 1;
        }

        while (d[l + re[l]] == d[l - re[l]]) {
            re[l]++;
        }

        if (re[l] + l > r) {
            r = re[l] + l;
            mid = l;
        }
        if ((re[l] - 1) % 2) {
            cnt[re[l] - 1]++;
        }
    }
}

int quick_pow(int a, int b) {
    a %= MOD;
    int res = 1;
    while (b) {
        if (b & 1) {
            res = res * a % MOD;
        }
        a = a * a % MOD;
        b >>= 1;
    }
    return res;
}