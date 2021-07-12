#include <climits>
#include <cstdio>
#include <iostream>

// bool vis[200050];
bool vis[2050];

int read();

int main() {
    freopen("color.in", "r", stdin);
    freopen("color.out", "w", stdout);

    int n = read(), mr = 0, ml = INT_MAX;
    while (n--) {
        int l = read(), r = read(), ans = 0;
        bool flag = false;
        mr = std::max(mr, r);
        ml = std::min(ml, l);
        for (int i = l; i <= r; i++) {
            vis[i] = true;
        }
        for (int i = ml - 1; i <= mr + 1; i++) {
            if (flag and vis[i]) {
                flag = false;
                ans++;
            }
            if (!vis[i]) {
                flag = true;
            }
        }
        std::cout << ans << '\n';
    }

    fclose(stdin);
    fclose(stdout);
    return 0;
}

int read() {
    int x = 0, f = 1, ch = getchar();
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