#include <cstdio>
#include <iostream>
#include <vector>

struct BigInteger {
    typedef unsigned long long LL;

    static const int BASE = 100000000;
    static const int WIDTH = 8;
    std::vector<int> s;

    BigInteger& clean() {
        while (!s.back() && s.size() > 1) s.pop_back();
        return *this;
    }
    BigInteger(LL num = 0) { *this = num; }
    BigInteger(std::string s) { *this = s; }
    BigInteger& operator=(long long num) {
        s.clear();
        do {
            s.push_back(num % BASE);
            num /= BASE;
        } while (num > 0);
        return *this;
    }
    BigInteger& operator=(const std::string& str) {
        s.clear();
        int x, len = (str.length() - 1) / WIDTH + 1;
        for (int i = 0; i < len; i++) {
            int end = str.length() - i * WIDTH;
            int start = std::max(0, end - WIDTH);
            sscanf(str.substr(start, end - start).c_str(), "%d", &x);
            s.push_back(x);
        }
        return (*this).clean();
    }

    BigInteger operator+(const BigInteger& b) const {
        BigInteger c;
        c.s.clear();
        for (int i = 0, g = 0;; i++) {
            if (g == 0 && i >= s.size() && i >= b.s.size()) break;
            int x = g;
            if (i < s.size()) x += s[i];
            if (i < b.s.size()) x += b.s[i];
            c.s.push_back(x % BASE);
            g = x / BASE;
        }
        return c;
    }
    BigInteger operator*(const BigInteger& b) const {
        int i, j;
        LL g;
        std::vector<LL> v(s.size() + b.s.size(), 0);
        BigInteger c;
        c.s.clear();
        for (i = 0; i < s.size(); i++)
            for (j = 0; j < b.s.size(); j++) v[i + j] += LL(s[i]) * b.s[j];
        for (i = 0, g = 0;; i++) {
            if (g == 0 && i >= v.size()) break;
            LL x = v[i] + g;
            c.s.push_back(x % BASE);
            g = x / BASE;
        }
        return c.clean();
    }
};

std::ostream& operator<<(std::ostream& out, const BigInteger& x) {
    out << x.s.back();
    for (int i = x.s.size() - 2; i >= 0; i--) {
        char buf[20];
        sprintf(buf, "%08d", x.s[i]);
        for (int j = 0; j < strlen(buf); j++) out << buf[j];
    }
    return out;
}

BigInteger dp[15050][2][2];

template <typename T>
T read();

int main() {
    freopen("phoenix.in", "r", stdin);
    freopen("phoenix.out", "w", stdout);

    int t = read<int>();
    while (t--) {
        int n = read<int>();
        for (int i = 0; i <= n; i++) {
            dp[i][0][0].clean();
            dp[i][0][1].clean();
            dp[i][1][0].clean();
            dp[i][1][1].clean();
        }

        dp[1][1][0] = 1;
        dp[1][0][1] = 1;
        dp[1][0][0] = 2;

        for (int i = 2; i <= n; i++) {
            for (int j = 0; j <= 1; j++)
                for (int k = 0; k <= 1; k++) {
                    dp[i][j][k] = dp[i - 1][j][k] * 2;
                    dp[i][j][k] = dp[i][j][k] + dp[i - 1][j ^ 1][k];
                    dp[i][j][k] = dp[i][j][k] + dp[i - 1][j][k ^ 1];
                }
        }

        std::cout << dp[n][0][0] << '\n';
    }

    fclose(stdin);
    fclose(stdout);
    return 0;
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