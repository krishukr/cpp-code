#include <algorithm>
#include <cmath>
#include <cstdio>
#include <iomanip>
#include <iostream>

const int MAX_N = 100050;

struct Poi {
    double x;
    double y;
} p[MAX_N], stk[MAX_N];

int cnt;

inline double multi(const Poi& al, const Poi& ar, const Poi& bl, const Poi& br);

inline double dis(const Poi& a, const Poi& b);

int main() {
    std::ios::sync_with_stdio(false);

    int n;
    std::cin >> n;
    for (int i = 1; i <= n; i++) {
        std::cin >> p[i].x >> p[i].y;
    }

    std::sort(p + 1, p + n + 1, [](const Poi& a, const Poi& b) -> bool {
        return a.x < b.x or (a.x == b.x and a.y < b.y);
    });
    stk[++cnt] = p[1];

    std::sort(p + 2, p + n + 1, [&](const Poi& a, const Poi& b) -> bool {
        auto t = multi(p[1], a, p[1], b);
        if (t > 0) {
            return true;
        }
        if (t == 0 and dis(p[1], a) < dis(p[1], b)) {
            return true;
        }
        return false;
    });
    stk[++cnt] = p[2];

    for (int i = 3; i <= n; i++) {
        while (cnt > 1 and multi(stk[cnt - 1], stk[cnt], stk[cnt], p[i]) <= 0) {
            cnt--;
        }
        stk[++cnt] = p[i];
    }
    stk[cnt + 1] = p[1];

    double sum = 0;
    for (int i = 1; i <= cnt; i++) {
        sum += dis(stk[i], stk[i + 1]);
    }
    std::cout << std::fixed << std::setprecision(2) << sum << '\n';

    return 0;
}

inline double multi(const Poi& al, const Poi& ar, const Poi& bl,
                    const Poi& br) {
    return (ar.x - al.x) * (br.y - bl.y) - (br.x - bl.x) * (ar.y - al.y);
}

inline double dis(const Poi& a, const Poi& b) {
    return std::sqrt((b.y - a.y) * (b.y - a.y) + (b.x - a.x) * (b.x - a.x));
}
