#include <iostream>

const int MAX_N = 100005;

int t[MAX_N], x[MAX_N], y[MAX_N];

inline int read();

int main() {
    std::ios::sync_with_stdio(false);
    freopen("charlotte.in", "r", stdin);
    freopen("charlotte.out", "w", stdout);

    int T = read();
    while (T--) {
        int n = read();
        bool flag = false;
        for (int i = 1; i <= n; i++) {
            t[i] = read(), x[i] = read(), y[i] = read();
        }

        if (abs(x[1] - 1) + abs(y[1] - 1) > t[1] or
            (abs((abs(x[1] - 1) + abs(y[1] - 1)) - t[1])) % 2) {
            std::cout << "No" << '\n';
            continue;
        }

        for (int i = 2; i <= n; i++) {
            if (abs(x[i] - x[i - 1]) + abs(y[i] - y[i - 1]) >
                    (t[i] - t[i - 1]) or
                (abs(abs(x[i] - x[i - 1]) + abs(y[i] - y[i - 1])) -
                 (t[i] - t[i - 1])) %
                    2) {
                std::cout << "No" << '\n';
                flag = true;
            }
        }
        if (!flag) {
            std::cout << "Yes" << '\n';
        }
    }

    fclose(stdin);
    fclose(stdout);
    return 0;
}

inline int read() {
    int x = 0, f = 1;
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