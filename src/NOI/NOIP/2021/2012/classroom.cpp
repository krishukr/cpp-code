#include <cstdio>
#include <iostream>

typedef long long ll;

const int MAX_N = 1000005;

int r[MAX_N], d[MAX_N], s[MAX_N], t[MAX_N];
ll diff[MAX_N], sum;

template <typename T>
T read();

int main() {
    std::ios::sync_with_stdio(false);

    int n = read<int>(), m = read<int>();

    for (int i = 1; i <= n; i++) {
        r[i] = read<int>();
    }

    for (int i = 1; i <= m; i++) {
        d[i] = read<int>(), s[i] = read<int>(), t[i] = read<int>();
        diff[s[i]] += d[i];
        diff[t[i] + 1] -= d[i];
    }

    int min = -1, tmp = m;
    bool flag = true;
    for (int i = 1; i <= n; i++) {
        sum += diff[i];

        if (sum > r[i]) {
            while (sum > r[i]) {
                diff[s[tmp]] -= d[tmp];
                diff[t[tmp] + 1] += d[tmp];
                if (s[tmp] <= i and i <= t[tmp]) {
                    sum -= d[tmp];
                }
                tmp--;
            }

            if (flag) {
                min = tmp;
                flag = false;
            } else {
                min = std::min(min, tmp);
            }
        }
    }

    if (min == -1) {
        std::cout << "0\n";
    } else {
        std::cout << "-1\n" << min + 1 << '\n';
    }

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