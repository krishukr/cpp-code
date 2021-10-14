#include <cstdio>
#include <cstring>
#include <iostream>
#include <vector>

typedef long long ll;

const int MOD = 1e9 + 7;

const int code[4][40] = {
    {0, 0, 0, 0, 0, 0, 0, 0},
    {1, 1, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0},
    {1, 1, 1, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0},
    {1, 1, 1, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0,
     1, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0}};

const int type[4][40] = {
    {0, 1, 1, 1, 1, 1, 1, 1},
    {0, 0, 0, 1, 1, 1, 1, 1, 0, 0, 1, 1, 1, 1, 1, 1},
    {0, 0, 0, 0, 1, 1, 1, 1, 0, 0, 1, 1, 1, 1, 1, 1, 0, 0, 1, 1, 1, 1, 1, 1},
    {0, 0, 0, 0, 0, 1, 1, 1, 0, 0, 1, 1, 1, 1, 1, 1,
     0, 0, 1, 1, 1, 1, 1, 1, 0, 0, 1, 1, 1, 1, 1, 1}};

std::string buffer;

ll quick_pow(ll a, ll b);

int main() {
    // std::ios::sync_with_stdio(false);
    freopen("utf.in", "r", stdin);
    freopen("utf.out", "w", stdout);

    int x;
    bool sa = true;
    std::cin >> x;

    ll res = 1, cnt = 0, ans = 1;
    for (int i = 1; i <= x; i++) {
        std::string s;
        std::cin >> s;

        if (s[0] != '0') {
            sa = false;
        }
        if (sa) {
            if (s == "00000000") {
                res = 0;
                sa = false;
                break;
            }
            cnt = 0;
            bool f = false;
            for (auto it : s) {
                if (it == '1') {
                    f = true;
                }
                if (it == '?') {
                    cnt++;
                }
            }
            if (f) {
                ans *= quick_pow(2, cnt);
            } else {
                ans *= quick_pow(2, cnt) - 1;
            }
            ans %= MOD;
        }

        buffer += s;

        bool flag = false;
        int n = buffer.size(), j, it;
        for (j = 0; j < 4; j++) {
            for (it = 0; it < n; it++) {
                int k = buffer[it] - '0';

                if (!type[j][it] and k != code[j][it]) {
                    break;
                }
            }
            if (it == 8 * (j + 1)) {
                buffer.clear();
            }
            if (it == n) {
                flag = true;
                break;
            }
        }

        if (j == 4 and !flag) {
            res = 0;
            break;
        }
    }

    if (sa) {
        std::cout << ans << '\n';
    } else {
        std::cout << res << '\n';
    }

    fclose(stdin);
    fclose(stdout);
    return 0;
}

ll quick_pow(ll a, ll b) {
    ll res = 1;
    while (b) {
        if (b & 1) {
            res = res * a % MOD;
        }
        a = a * a % MOD;
        b >>= 1;
    }
    return res;
}
