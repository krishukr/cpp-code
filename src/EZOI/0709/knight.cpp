#include <cstring>
#include <iostream>

const int MAX_N = 100050;
const int MAX_M = 15;

#pragma region initial
long long x[MAX_N], y[MAX_N];
long long max_x[MAX_M], max_y[MAX_M];
long long min_x[MAX_M], min_y[MAX_M];
long long max_row[MAX_M], max_col[MAX_M];
long long min_row[MAX_M], min_col[MAX_M];
long long ans[MAX_M];

inline int read();
#pragma endregion initial

int main() {
    freopen("knight.in", "r", stdin);
    freopen("knight.out", "w", stdout);

    int n = read(), m = read();
    memset(min_x, 0x7f, sizeof(min_x));
    memset(min_y, 0x7f, sizeof(min_y));
    memset(min_row, 0x7f, sizeof(min_row));
    memset(min_col, 0x7f, sizeof(min_col));

    for (int i = 1; i <= m; i++) {
        x[i] = read(), y[i] = read();

        max_x[x[i]] = std::max(max_x[x[i]], y[i]);
        min_x[x[i]] = std::min(min_x[x[i]], y[i]);
        max_y[y[i]] = std::max(max_y[y[i]], x[i]);
        min_y[y[i]] = std::min(min_y[y[i]], x[i]);

        max_row[n + x[i] - y[i]] = std::max(max_row[n + x[i] - y[i]], x[i]);
        min_row[n + x[i] - y[i]] = std::min(min_row[n + x[i] - y[i]], x[i]);
        max_col[x[i] + y[i]] = std::max(max_col[x[i] + y[i]], x[i]);
        min_col[x[i] + y[i]] = std::min(min_col[x[i] + y[i]], x[i]);
    }

    for (int i = 1; i <= m; i++) {
        int cnt = 0;
        if (max_x[x[i]] > y[i]) {
            cnt++;
        }
        if (min_x[x[i]] < y[i]) {
            cnt++;
        }
        if (max_y[y[i]] > x[i]) {
            cnt++;
        }
        if (min_y[y[i]] < x[i]) {
            cnt++;
        }
        if (max_row[n + x[i] - y[i]] > x[i]) {
            cnt++;
        }
        if (min_row[n + x[i] - y[i]] < x[i]) {
            cnt++;
        }
        if (max_col[x[i] + y[i]] > x[i]) {
            cnt++;
        }
        if (min_col[x[i] + y[i]] < x[i]) {
            cnt++;
        }
        ans[cnt]++;
    }

    for (int i = 0; i <= 8; i++) {
        std::cout << ans[i] << ' ';
    }
    std::cout << '\n';

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