#include <cstdio>
#include <iostream>

const int MAX_N = 2050;

struct Poi {
    double x;
    double y;
};

struct Lin {
    Poi l;
    Poi r;
} lin[MAX_N];

inline double multi(const Poi& a, const Poi& b, const Poi& c);

bool check(const Lin& a, const Lin& b);

int main() {
    std::ios::sync_with_stdio(false);

    while (!std::cin.eof()) {
        int n = 0;
        std::cin >> n;
        if (!n) {
            break;
        }

        for (int i = 1; i <= n; i++) {
            std::cin >> lin[i].l.x >> lin[i].l.y >> lin[i].r.x >> lin[i].r.y;
        }

        for (int i = 1; i <= n; i++) {
            for (int j = i + 1; j <= n; j++) {
                if (check(lin[i], lin[j])) {
                    std::cout << "burned!\n";
                    goto end;
                }
            }
        }

        std::cout << "ok!\n";
    end:
        continue;
    }

    return 0;
}

inline double multi(const Poi& a, const Poi& b, const Poi& c) {
    return (a.x - b.x) * (a.y - c.y) - (a.y - b.y) * (a.x - c.x);
}

bool check(const Lin& a, const Lin& b) {
    if (std::max(a.l.x, a.r.x) < std::min(b.l.x, b.r.x)) return false;
    if (std::max(a.l.y, a.r.y) < std::min(b.l.y, b.r.y)) return false;
    if (std::max(b.l.x, b.r.x) < std::min(a.l.x, a.r.x)) return false;
    if (std::max(b.l.y, b.r.y) < std::min(a.l.y, a.r.y)) return false;

    if (multi(a.l, b.l, a.r) * multi(a.l, a.r, b.r) < 0) return false;
    if (multi(b.l, a.l, b.r) * multi(b.l, b.r, a.r) < 0) return false;

    return true;
}
