#include <algorithm>
#include <iostream>

using std::cin;
using std::cout;

int dfs(int x, int y, int p);

int main() {
    std::ios::sync_with_stdio(false);
    int T;
    cin >> T;
    while (T--) {
        int m, n;
        cin >> m >> n;
        if (dfs(std::min(m, n), std::max(m, n), 0)) {
            cout << "Ollie wins\n";
        } else {
            cout << "Stan wins\n";
        }
    }

    return 0;
}

int dfs(int x, int y, int p) {
    if (x == y) {
        return p;
    }
    if (y / x >= 2) {
        return p;
    }
    return dfs(y - x, x, p ^ 1);
}