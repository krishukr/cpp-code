#include <iostream>

using namespace std;

const int MAX_N = 1e8 + 1;

bool is_prime[MAX_N];
int prime[MAX_N], count;

int main() {
    ios::sync_with_stdio(false);
    int n, q;
    cin >> n >> q;
    for (int i = 2; i * i <= n; i++) {
        if (is_prime[i]) continue;
        for (int j = i * i; j <= n; j += i) {
            is_prime[j] = true;
        }
    }
    for (int i = 2; i <= n; i++) {
        if (!is_prime[i]) {
            prime[count++] = i;
        }
    }
    for (int i = 0; i < q; i++) {
        int x;
        cin >> x;
        cout << prime[x - 1] << endl;
    }

    return 0;
}