#include <iostream>

template <typename T>
T read();

int map[1001][1001];

int main() {
    freopen("drama.in", "r", stdin);
    freopen("drama.out", "w", stdout);

    int n = read<int>(), m = read<int>();
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= m; j++) {
            map[i][j] = read<int>();
            map[i][0] ^= map[i][j];
        }
        // std::cout << map[i][0] << '\n';
    }
    int q = read<int>();
    for (int i = 1; i <= q; i++) {
        int op = read<int>();
        if (op == 1) {
            int l = read<int>(), r = read<int>(), ans = 0;
            for (int j = l; j <= r; j++) {
                if (!map[j][0]) {
                    ans++;
                }
            }
            std::cout << ans << '\n';
        } else {
            int x1 = read<int>(), y1 = read<int>(), x2 = read<int>(),
                y2 = read<int>(), p = read<int>();
            for (int j = y1; j <= y2; j++) {
                for (int k = x1; k <= x2; k++) {
                    map[j][k] ^= p;
                }
            }
            for (int i = 1; i <= n; i++) {
                map[i][0] = 0;
                for (int j = 1; j <= m; j++) {
                    map[i][0] ^= map[i][j];
                }
                // std::cout << map[i][0] << '\n';
            }
        }
    }

    fclose(stdin);
    fclose(stdout);
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