#include <cstdio>
#include <iostream>

const int MAX_N = 200000;

int num[MAX_N], color[MAX_N];
int pre, ans;

template <typename T>
T read();

int main() {
    freopen("hotel.in", "r", stdin);
    freopen("hotel.out", "w", stdout);

    int n = read<int>(), k = read<int>(), p = read<int>();
    for (int i = 1; i <= n; i++) {
        color[i] = read<int>();
        int x = read<int>();
        if (x <= p) {
            for (int j = i; j > pre; j--) {
                num[color[j]]++;
            }
            pre = i;
            ans += num[color[i]] - 1;
        } else {
            ans += num[color[i]];
        }
    }
    std::cout << ans << '\n';

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