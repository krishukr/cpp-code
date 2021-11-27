#include <cstdio>
#include <iostream>
#include <map>

const int MAX_N = 505;

int n;

template <typename T>
T read();

struct Mat {
    Mat() = default;
    ~Mat() = default;

    int d[MAX_N][MAX_N];

    void in();
    void out();

    Mat operator*(const Mat &x) const;
    bool operator<(const Mat &x) const;
};

int main() {
    std::ios::sync_with_stdio(false);

    n = read<int>();
    int m = read<int>();
    Mat a;
    a.in();

    std::map<Mat, int> vis;
    std::map<int, Mat> rep;
    Mat r = a;
    vis[r] = 1;
    rep[1] = r;

    for (int i = 2; i <= m; i++) {
        r = r * a;
        if (vis.count(r)) {
            int p = vis[r];
            r = rep[(m - p) % (i - p) + p];
            break;
        } else {
            vis[r] = i;
            rep[i] = r;
        }
    }
    r.out();

    return 0;
}

void Mat::in() {
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= n; j++) {
            d[i][j] = read<int>();
        }
    }
}

void Mat::out() {
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= n; j++) {
            std::cout << d[i][j] << ' ';
        }
        std::cout << '\n';
    }
}

Mat Mat::operator*(const Mat &x) const {
    Mat r = {};

    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= n; j++) {
            for (int k = 1; k <= n; k++) {
                r.d[i][j] |= (d[i][k] ^ x.d[k][j]);
            }
        }
    }
    return r;
}

bool Mat::operator<(const Mat &x) const {
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= n; j++) {
            if (d[i][j] != x.d[i][j]) {
                return d[i][j] < x.d[i][j];
            }
        }
    }
    return false;
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