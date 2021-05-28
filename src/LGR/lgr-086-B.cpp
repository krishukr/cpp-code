#include <bits/stl_algobase.h>

#include <cstdio>
#include <iostream>

using std::cout;

int main() {
    std::ios::sync_with_stdio(false);

    int n, ans = 0, pre = -1;
    scanf("%d", &n);

    for (int i = 0; i < n; i++) {
        int x;
        scanf("%d", &x);
        if (x == pre and x != 0) {
            x++;
            pre = x - 1;
        } else {
            pre = x;
        }
        ans = std::max(x, ans);
    }

    cout << ans << "\n";

    return 0;
}