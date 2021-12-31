#include <cstdio>
#include <cstring>
#include <iostream>
#include <vector>

#ifndef NDEBUG
#define NDEBUG
#endif

#include <cassert>

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

    BigInt operator%(const BigInt& b) {
        while (*this >= b) {
            *this = *this - b;
        }
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
    bool operator>=(const BigInt& b) const { return !(*this < b); }

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
        if (in >> s) {
            x = s;
            return in;
        } else {
            return in;
        }
    }
};

template <typename T>
T gcd(T m, T n);

int main() {
    std::ios::sync_with_stdio(false);

    BigInt a, b;
    std::cin >> a >> b;
    std::cout << gcd(a, b) << '\n';

    return 0;
}

template <typename T>
T gcd(T m, T n) {
    T t;
    while (n > 0) {
        t = m % n;
        m = n;
        n = t;
    }
    return m;
}
