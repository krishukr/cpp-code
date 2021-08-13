#include <cstdio>
#include <iostream>

using std::cout;

int main() {
    std::ios::sync_with_stdio(false);
    int T;
    scanf("%d", &T);

    while (T--) {
        long long n, k, s, x;
        scanf("%lld %lld %lld", &n, &k, &s);
        x = (n - k + 1 + n) * k / 2;

        if (x < s) {
            cout << "No\n";
        } else if (x == s) {
            cout << "Yes\n";
        } else {
            x = (1 + k) * k / 2;
            if (x > s) {
                cout << "No\n";
            } else {
                cout << "Yes\n";
            }
        }
    }

    return 0;
}