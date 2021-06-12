#include <climits>
#include <cstring>
#include <iostream>

const int MAX_N = 101;

int map[MAX_N][MAX_N], a[MAX_N];

int arr(int x[], int n);

int main() {
    std::ios::sync_with_stdio(false);

    int n, ans = INT_MIN, tmp;
    std::cin >> n;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            std::cin >> map[i][j];
        }
    }
    for (int i = 0; i < n; i++) {
        memset(a, 0, sizeof(a));
        for (int j = i; j < n; j++) {
            for (int k = 0; k < n; k++) {
                a[k] += map[j][k];
            }
            tmp = arr(a, n);
            if (tmp > ans) {
                ans = tmp;
            }
        }
    }

    std::cout << ans << '\n';

    return 0;
}

int arr(int x[], int n) {
    int res = INT_MIN, tmp = -1;
    for (int i = 0; i < n; i++) {
        if (tmp > 0) {
            tmp += x[i];
        } else {
            tmp = x[i];
        }
        if (tmp > res) {
            res = tmp;
        }
    }
    return res;
}