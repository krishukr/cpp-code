#include <cstdio>
#include <iostream>

using ll = long long;

constexpr ll days[2][13] = {
    {0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31},
    {0, 31, 29, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31}};

ll check(ll x);

void calc(ll x, ll y);

template <typename T>
T read();

template <typename T>
void read(T& t);

template <typename T, typename... Args>
void read(T& t, Args&... rest);

int main() {
    freopen("julian.in", "r", stdin);
    freopen("julian.out", "w", stdout);
    std::ios::sync_with_stdio(false);

    int Q;
    read(Q);
    while (Q--) {
        ll x;
        read(x);
        int l{-4712}, r{(int)1e9 + 10};
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

    std::cout << std::flush;
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

        if (y < 1582 and !(y % 4)) {
            r = 1;
        }
        if (y > 1582) {
            if (!(y % 400) or (!(y % 4) and (y % 100))) {
                r = 1;
            }
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

template <typename T>
void read(T& t) {
    t = read<T>();
}

template <typename T, typename... Args>
void read(T& t, Args&... rest) {
    t = read<T>();
    read(rest...);
}