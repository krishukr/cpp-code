#include <bits/stdc++.h>

struct BigInt {
    const static int BASE = 100000000;
    const static int WIDTH = 8;

    std::vector<int> s;

    BigInt(unsigned long long num = 0) { *this = num; }
    BigInt(std::string s) { *this = s; }

    BigInt& clean() {
        while (!s.back() and !s.empty()) {
            s.pop_back();
        }
        return *this;
    }

    BigInt& operator=(unsigned long long num) {
        s.clear();
        do {
            s.push_back(num % BASE);
            num /= BASE;
        } while (num > 0);
        return *this;
    }
    BigInt& operator=(const std::string& str) {
        s.clear();
        int x, len = (str.length() - 1) / WIDTH + 1;

        for (int i = 0; i < len; i++) {
            int r = str.length() - i * WIDTH;
            int l = std::max(0, r - WIDTH);
            sscanf(str.substr(l, r - l).c_str(), "%d", &x);
            s.push_back(x);
        }

        return (*this).clean();
    }

    BigInt operator+(const BigInt& b) const {
        BigInt r;
        r.s.clear();
        int i = 0, g = 0;

        while (true) {
            if (g == 0 and i >= s.size() and i >= b.s.size()) {
                break;
            }
            int x = g;
            if (i < s.size()) {
                x += s[i];
            }
            if (i < b.s.size()) {
                x += b.s[i];
            }

            r.s.push_back(x % BASE);
            g = x / BASE;
            i++;
        }
        return r;
    }

    BigInt operator-(const BigInt& b) const {
        assert(b <= *this);
        BigInt r;
        r.s.clear();
        int i = 0, g = 0;

        while (true) {
            if (g == 0 && i >= s.size() && i >= b.s.size()) {
                break;
            }
            int x = s[i] + g;
            if (i < b.s.size()) {
                x -= b.s[i];
            }
            if (x < 0) {
                g = -1;
                x += BASE;
            } else {
                g = 0;
            }

            r.s.push_back(x);
            i++;
        }
        return r.clean();
    }

    BigInt operator*(const BigInt& b) const {
        int i, j;
        unsigned long long g;
        std::vector<unsigned long long> v(s.size() + b.s.size(), 0);
        BigInt c;
        c.s.clear();

        for (i = 0; i < s.size(); i++) {
            for (j = 0; j < b.s.size(); j++) {
                v[i + j] += (unsigned long long)(s[i]) * b.s[j];
            }
        }

        i = 0, g = 0;
        while (true) {
            if (g == 0 && i >= v.size()) {
                break;
            }
            unsigned long long x = v[i] + g;
            c.s.push_back(x % BASE);
            g = x / BASE;
            i++;
        }
        return c.clean();
    }

    BigInt operator/(const BigInt& b) const {
        assert(b > 0);
        BigInt c = *this;
        BigInt m;

        for (int i = s.size() - 1; i >= 0; i--) {
            m = m * BASE + s[i];
            c.s[i] = bsearch(b, m);
            m -= b * c.s[i];
        }
        return c.clean();
    }
    BigInt operator%(const BigInt& b) const {
        BigInt c = *this;
        BigInt m;
        for (int i = s.size() - 1; i >= 0; i--) {
            m = m * BASE + s[i];
            c.s[i] = bsearch(b, m);
            m -= b * c.s[i];
        }
        return m;
    }

    int bsearch(const BigInt& b, const BigInt& m) const {
        int L = 0, R = BASE - 1, x;
        while (true) {
            x = (L + R) >> 1;
            if (b * x <= m) {
                if (b * (x + 1) > m) {
                    return x;
                } else {
                    L = x;
                }
            } else {
                R = x;
            }
        }
    }

    BigInt& operator+=(const BigInt& b) {
        *this = *this + b;
        return *this;
    }
    BigInt& operator-=(const BigInt& b) {
        *this = *this - b;
        return *this;
    }
    BigInt& operator*=(const BigInt& b) {
        *this = *this * b;
        return *this;
    }
    BigInt& operator/=(const BigInt& b) {
        *this = *this / b;
        return *this;
    }
    BigInt& operator%=(const BigInt& b) {
        *this = *this % b;
        return *this;
    }

    bool operator<(const BigInt& b) const {
        if (s.size() != b.s.size()) {
            return s.size() < b.s.size();
        }
        for (int i = s.size() - 1; i >= 0; i--) {
            if (s[i] != b.s[i]) {
                return s[i] < b.s[i];
            }
        }
        return false;
    }
    bool operator>(const BigInt& b) const { return b < *this; }
    bool operator<=(const BigInt& b) const { return !(b < *this); }
    bool operator>=(const BigInt& b) const { return !(*this < b); }
    bool operator!=(const BigInt& b) const { return b < *this || *this < b; }
    bool operator==(const BigInt& b) const {
        return !(b < *this) && !(b > *this);
    }

    friend std::ostream& operator<<(std::ostream& out, const BigInt& x) {
        out << x.s.back();

        for (int i = x.s.size() - 2; i >= 0; i--) {
            char buf[20];
            sprintf(buf, "%08d", x.s[i]);
            for (int j = 0; j < strlen(buf); j++) {
                out << buf[j];
            }
        }
        return out;
    }

    friend std::istream& operator>>(std::istream& in, BigInt& x) {
        std::string s;
        if (std::cin >> s) {
            x = s;
            return in;
        } else {
            return in;
        }
    }
};

constexpr int MAX_N = 5050;

int a[MAX_N], f[MAX_N];
BigInt g[MAX_N];

template <typename T>
T read();

template <typename T>
void read(T& t);

template <typename T, typename... Args>
void read(T& t, Args&... rest);

int main() {
    std::ios::sync_with_stdio(false);

    a[0] = INT_MAX;
    g[0] = 1;

    int n;
    read(n);
    for (int i = 1; i <= n; i++) {
        read(a[i]);
    }
    for (int i = 1; i <= n; i++) {
        for (int j = i - 1; j >= 0; j--) {
            if (a[i] < a[j] and f[i] <= f[j]) {
                f[i] = f[j] + 1;
            }
        }
        for (int j = i - 1; j >= 0; j--) {
            if (a[i] < a[j] and f[i] == f[j] + 1) {
                g[i] += g[j];
            } else if (a[i] == a[j] and f[i] == f[j]) {
                break;
            }
        }
    }

    BigInt ans{};
    int x{};
    for (int i = 1; i <= n; i++) {
        if (x < f[i]) {
            x = f[i];
            ans = g[i];
        } else if (x == f[i]) {
            ans += g[i];
        }
    }
    std::cout << x << ' ' << ans << '\n';

    return 0;
}

template <typename T>
T read() {
    T x = 0, f = 1;
    char ch = getchar_unlocked();
    while (!isdigit(ch)) {
        if (ch == '-') f = -1;
        ch = getchar_unlocked();
    }
    while (isdigit(ch)) {
        x = x * 10 + ch - 48;
        ch = getchar_unlocked();
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