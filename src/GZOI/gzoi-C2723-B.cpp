#include <cstdio>
#include <iostream>

using ll = long long;

constexpr int MAX_N = 100050;
constexpr int MAX_M = 25;

struct Mat {
    int m[MAX_M][MAX_M];

    Mat(const int n);
    Mat operator*(const Mat& x) const;
};

int nxt[MAX_M];
int f[MAX_N][MAX_M], g[MAX_M][MAX_M];
int n, m, MOD;

void init(std::string s);

template <typename T, typename U>
T quick_pow(T a, U b);

int main() {
    std::ios::sync_with_stdio(false);

    std::cin >> n >> m >> MOD;
    std::string s;
    std::cin >> s;
    init(s);

    Mat a{0}, b{0};
    nxt[0] = 0;
    for (int i = 0; i < m; i++) {
        for (char j = '0'; j <= '9'; j++) {
            int k = i;
            while (s[k] != j and k > 0) {
                k = nxt[k];
            }
            if (s[k] == j) {
                k++;
            }
            if (k < m) {
                b.m[i][k]++;
            }
        }
    }

    b = quick_pow(b, n);
    a.m[0][0] = 1;
    a = a * b;
    int ans{};
    for (int i = 0; i < m; i++) {
        ans += a.m[0][i];
        ans %= MOD;
    }
    std::cout << ans << '\n';

    return 0;
}

Mat::Mat(const int n) {
    for (int i = 0; i < MAX_M; i++) {
        for (int j = 0; j < MAX_M; j++) {
            this->m[i][j] = 0;
        }
    }
    for (int i = 0; i < MAX_M; i++) {
        this->m[i][i] = n;
    }
}

Mat Mat::operator*(const Mat& x) const {
    Mat r{0};
    for (int i = 0; i < MAX_M; i++) {
        for (int k = 0; k < MAX_M; k++) {
            for (int j = 0; j < MAX_M; j++) {
                r.m[i][j] += m[i][k] * x.m[k][j];
                r.m[i][j] %= MOD;
            }
        }
    }
    return r;
}

void init(std::string s) {
    int i = 0, j;
    nxt[0] = j = -1;
    while (i < s.length()) {
        if (j == -1 or s[i] == s[j]) {
            nxt[++i] = ++j;
        } else {
            j = nxt[j];
        }
    }
}

template <typename T, typename U>
T quick_pow(T a, U b) {
    T r{1};
    while (b) {
        if (b & 1) {
            r = r * a;
        }
        a = a * a;
        b >>= 1;
    }
    return r;
}