#include <cstdio>
#include <iostream>

using std::cout;

int main() {
    std::ios::sync_with_stdio(false);

    int n;
    scanf("%d", &n);

    for (int i = 1; i < n; i++) {
        cout << i << " ";
    }
    cout << "\n";
    fflush(stdout);

    return 0;
}