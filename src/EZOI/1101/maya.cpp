#include <cstdio>
#include <iostream>

typedef long long ll;

const ll days[2][13] = {{0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31},
                        {0, 31, 29, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31}};

ll a, b, c, d, e, f, g, h, i;

ll check(ll x);

void calc(ll x, ll y);

int main() {
    freopen("maya.in", "r", stdin);
    freopen("maya.out", "w", stdout);

    int t;
    std::cin >> t;
    while (t--) {
        std::string s;
        std::cin >> s;
        ll x = 584283ll;

        sscanf(s.data(), " %lld.%lld.%lld.%lld.%lld.%lld.%lld.%lld.%lld ", &a,
               &b, &c, &d, &e, &f, &g, &h, &i);

        x += i + 20ll * h + 360ll * g + 7200ll * f + 144000ll * e +
             2880000ll * d + 57600000 * c + 1152000000 * b + 23040000000 * a;

        ll l = -4712, r = 1e10 + 10;
        while (l <= r) {
            int mid = (l + r) / 2;
            if (check(mid) <= x) {
                l = mid + 1;
            } else {
                r = mid - 1;
            }
        }
        calc(x - check(l - 1), l);
    }

    fclose(stdin);
    fclose(stdout);
    return 0;
}

ll check(ll x) {
    if (x < -4712) {
        return 0;
    }

    ll res = 0;
    if (x < 1582) {
        res += (x + 4713) * 365;
        res += (x + 4712) / 4 + 1;
    } else {
        res = 2298874ll;
        res += (x - 1581) * 365;
        if (x > 1583) {
            res += (x - 1584) / 4 + 1;
        }
        if (x >= 1600) {
            res -= std::max(0ll, (x - 1600) / 100 + 1);
            res += std::max(0ll, (x - 1600) / 400 + 1);
        }
    }
    return res;
}

void calc(ll x, ll y) {
    ll m = 1, d = 1;
    while (x) {
        ll r = 0;

        if (y == 1582 and m == 10 and x >= 4) {
            x += 10;
        }
        if (!(y % 400) or (!(y % 4) and (y % 100))) {
            r = 1;
        }

        if (x >= days[r][m]) {
            x -= days[r][m];
            m++;
        } else {
            d += x;
            break;
        }
    }

    if (y <= 0) {
        y--;
    }
    std::cout << d << ' ' << m << ' ' << std::abs(y) << ' ';
    if (y < 0) {
        std::cout << "BC";
    }
    std::cout << '\n';
}