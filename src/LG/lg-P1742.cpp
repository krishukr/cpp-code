#include <algorithm>
#include <cmath>
#include <cstdio>
#include <iomanip>
#include <iostream>

constexpr int MAX_N = 100050;

struct Vect {
    double x, y;

    Vect operator+(const Vect& v) const { return {x + v.x, y + v.y}; }
    Vect operator-(const Vect& v) const { return {x - v.x, y - v.y}; }
    Vect operator*(const double& v) const { return {x * v, y * v}; }
    Vect operator/(const double& v) const { return {x / v, y / v}; }

    double operator*(const Vect& v) const { return x * v.y - y * v.x; }

    double len() const { return x * x + y * y; }

    Vect rotate_90() { return {y, -x}; }

    friend std::istream& operator>>(std::istream& i, Vect& v) {
        double x, y;
        if (i >> x >> y) {
            v = {x, y};
            return i;
        } else {
            return i;
        }
    }

    friend std::ostream& operator<<(std::ostream& o, const Vect& v) {
        o << v.x << ' ' << v.y;
        return o;
    }
} poi[MAX_N];

inline Vect cal(const Vect& p0, const Vect& v0, const Vect& p1,
                const Vect& v1) {
    return p0 + v0 * (((p1 - p0) * v1) / (v0 * v1));
}
inline Vect cir(const Vect& a, const Vect& b, const Vect& c) {
    return cal((a + b) / 2, (b - a).rotate_90(), (a + c) / 2,
               (c - a).rotate_90());
}

int main() {
    std::ios::sync_with_stdio(false);

    int n;
    std::cin >> n;
    for (int i = 1; i <= n; i++) {
        std::cin >> poi[i];
    }
    std::random_shuffle(poi + 1, poi + n + 1);

    Vect o;
    double r = 0;
    for (int i = 1; i <= n; i++) {
        if ((poi[i] - o).len() > r) {
            o = poi[i];
            r = 0;
            for (int j = 1; j < i; j++) {
                if ((poi[j] - o).len() > r) {
                    o = (poi[i] + poi[j]) / 2;
                    r = (poi[j] - o).len();
                    for (int k = 1; k < j; k++) {
                        if ((poi[k] - o).len() > r) {
                            o = cir(poi[i], poi[j], poi[k]);
                            r = (poi[k] - o).len();
                        }
                    }
                }
            }
        }
    }

    std::cout << std::fixed << std::setprecision(10);
    std::cout << std::sqrt(r) << '\n';
    std::cout << o << '\n';

    return 0;
}