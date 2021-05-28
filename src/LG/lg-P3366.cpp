#include <cstring>
#include <iostream>

using namespace std;

const int MAX_N = 5001;
int map[MAX_N][MAX_N];
bool is_view[MAX_N];

int main() {
    int n, min[MAX_N], m;
    cin >> n >> m;
    memset(map, 0x7f, sizeof(map));
    for (int i = 1; i <= m; i++) {
        int x, y, c;
        cin >> x >> y >> c;
        if (map[x][y] != 0x7f) {
            c = std::min(c, map[x][y]);
        }
        map[x][y] = c;
        map[y][x] = c;
    }
    memset(min, 0x7f - 1, sizeof(min));
    min[1] = 0;
    for (int i = 1; i <= n; i++) {
        int lowest = 0;
        for (int j = 1; j <= n; j++) {
            if (!is_view[j] and (min[j] < min[lowest])) {
                lowest = j;
            }
        }
        is_view[lowest] = true;
        for (int j = 1; j <= n; j++) {
            if (!is_view[j] and (map[lowest][j] < min[j])) {
                min[j] = map[lowest][j];
            }
        }
    }
    int total = 0;
    for (int i = 1; i <= n; i++) {
        total += min[i];
    }
    cout << total;

    return 0;
}