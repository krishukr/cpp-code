#include <cmath>
#include <cstdio>
#include <iomanip>
#include <iostream>

constexpr int MAX_N = 4050;
constexpr double EPS = 1e-8;

struct Vect {
    double x;
    double y;
    double z;

    Vect operator-(const Vect &v) const {
        return Vect{x - v.x, y - v.y, z - v.z};
    }
    Vect operator/(const Vect &v) const {
        return Vect{y * v.z - z * v.y, z * v.x - x * v.z, x * v.y - y * v.x};
    }
    double operator*(const Vect &v) const {
        return x * v.x + y * v.y + z * v.z;
    }

    static double rd() { return rand() % 2 ? EPS : -EPS; }

    double ml() const { return std::sqrt(x * x + y * y + z * z); }
    void pe() {
        x += rd();
        y += rd();
        z += rd();
    }
} pts[MAX_N];

struct Plane {
    int v[3];
    Vect tm() { return (pts[v[1]] - pts[v[0]]) / (pts[v[2]] - pts[v[0]]); }
} res[MAX_N << 1], del[MAX_N << 1], face[MAX_N << 1];

inline bool gtr(const double &x, const double &y) { return x - y > EPS; }
inline bool equ(const double &x, const double &y) {
    return x - y > -EPS and x - y < EPS;
}

inline double dis(const Vect &x, const Vect &y) { return (x - y).ml(); }
inline double dis(const Vect &x, const Vect &y, const Vect &z) {
    return ((z - y) / (x - y)).ml() / (z - y).ml();
}

inline bool is_above(const Vect &v, Plane &p) {
    return gtr((v - pts[p.v[0]]) * p.tm(), 0.0);
}

int vis[MAX_N][MAX_N];

int calc(int totp);

int main() {
    std::ios::sync_with_stdio(false);

    int n;
    std::cin >> n;
    for (int i = 1; i <= n; i++) {
        std::cin >> pts[i].x >> pts[i].y >> pts[i].z;
        pts[i].pe();
    }

    int r = calc(n);
    double ans = 0;
    for (int i = 1; i <= r; i++) {
        ans += face[i].tm().ml() / 2;
    }
    std::cout << std::fixed << std::setprecision(3) << ans << '\n';

    return 0;
}

int calc(int totp) {
    int totf = 0;
    face[++totf] = Plane{0, 1, 2};
    face[++totf] = Plane{0, 2, 1};

    for (int i = 1; i <= totp; i++) {
        int totr = 0, totd = 0;

        for (int j = 1; j <= totf; j++) {
            if (!is_above(pts[i], face[j])) {
                res[++totr] = face[j];
            } else {
                del[++totd] = face[j];
                for (int k = 0; k < 3; k++) {
                    vis[face[j].v[k]][face[j].v[(k + 1) % 3]] = i + 1;
                }
            }
        }

        for (int j = 1; j <= totd; j++) {
            auto f = del[j];
            for (int k = 0; k < 3; k++) {
                if (vis[f.v[k]][f.v[(k + 1) % 3]] == i + 1 and
                    vis[f.v[(k + 1) % 3]][f.v[k]] != i + 1) {
                    res[++totr] = Plane{f.v[k], f.v[(k + 1) % 3], i};
                }
            }
        }

        totf = totr;
        for (int j = 1; j <= totr; j++) {
            face[j] = res[j];
        }
    }

    return totf;
}