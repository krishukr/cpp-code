#include <cstdio>
#include <iostream>
#include <queue>
#include <set>

struct Mat {
    const static int SIZ = 3;

    int m[5][5];

    inline bool operator<(const Mat& x) const {
        for (int i = 1; i <= SIZ; i++) {
            for (int j = 1; j <= SIZ; j++) {
                if (m[i][j] != x.m[i][j]) {
                    return m[i][j] < x.m[i][j];
                }
            }
        }
        return false;
    }

    inline int operator-(const Mat& x) const {
        int res = 0;
        for (int i = 1; i <= SIZ; i++) {
            for (int j = 1; j <= SIZ; j++) {
                if (m[i][j] != x.m[i][j]) {
                    res++;
                }
            }
        }
        return res;
    }
};

const Mat stdm = {{{}, {0, 1, 2, 3}, {0, 8, 0, 4}, {0, 7, 6, 5}, {}}};

struct Node {
    Mat m;
    int stp;

    inline bool operator>(const Node& x) const {
        return stp + stp + (m - stdm) > x.stp + x.stp + (x.m - stdm);
    }

    inline int operator-(const Mat& x) const { return m - x; }

    friend std::ostream& operator<<(std::ostream& o, const Node& x) {
        o << x.stp;
        return o;
    }
};

std::priority_queue<Node, std::vector<Node>, std::greater<Node>> q;
std::set<Mat> s;

const int dx[5] = {0, 1, 0, -1, 0}, dy[5] = {0, 0, 1, 0, -1};

int main() {
    std::ios::sync_with_stdio(false);

    Mat bg{};
    for (int i = 1; i <= 3; i++) {
        for (int j = 1; j <= 3; j++) {
            char ch;
            std::cin >> ch;
            bg.m[i][j] = ch - 48;
        }
    }
    q.push((Node){bg, 0});

    while (!q.empty()) {
        auto p = q.top();
        q.pop();

        if (p - stdm == 0) {
            std::cout << p << '\n';
            return 0;
        }

        int x, y;
        for (int i = 1; i <= 3; i++) {
            for (int j = 1; j <= 3; j++) {
                if (p.m.m[i][j] == 0) {
                    x = i;
                    y = j;
                }
            }
        }

        for (int i = 1; i <= 4; i++) {
            int xx = x + dx[i], yy = y + dy[i];
            if (xx < 1 or xx > 3 or yy < 1 or yy > 3) {
                continue;
            }

            std::swap(p.m.m[x][y], p.m.m[xx][yy]);
            if (!s.count(p.m)) {
                s.insert(p.m);
                q.push({p.m, p.stp + 1});
            }

            std::swap(p.m.m[x][y], p.m.m[xx][yy]);
        }
    }

    return 0;
}