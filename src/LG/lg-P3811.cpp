#include <cstdio>

using namespace std;

const int MAX_N = 3 * 1e6 + 1;

long long inv[MAX_N];

int main() {
    int n, p;
    scanf("%d %d", &n, &p);
    inv[1] = 1;
    printf("1\n");
    for (int i = 2; i <= n; i++) {
        inv[i] = (long long)(p - p / i) * inv[p % i] % p;
        printf("%lld\n", inv[i]);
    }

    return 0;
}
