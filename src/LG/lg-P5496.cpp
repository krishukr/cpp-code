#include <cstdio>
#include <cstring>
#include <iostream>

class PAM {
   protected:
    const static int CHA_SIZE = 26;
    const static int MAX_N = 500050;

    struct Node {
        int ch[CHA_SIZE];
        int fil;
        int len;
        int num;
    } node[MAX_N];

    int siz, len, lst, cnt;
    int s[MAX_N];

    int get_fail(int x) {
        while (s[siz - node[x].len - 1] != s[siz]) {
            x = node[x].fil;
        }
        return x;
    }

   public:
    PAM() {
        node[0].len = 0;
        node[0].fil = 1;
        node[1].len = -1;
        node[1].fil = 0;

        lst = 0;
        cnt = 1;
    }

    void build() {
        int p = get_fail(lst);
        if (!node[p].ch[s[siz]]) {
            node[++cnt].len = node[p].len + 2;
            node[cnt].fil = node[get_fail(node[p].fil)].ch[s[siz]];
            node[cnt].num = node[node[cnt].fil].num + 1;
            node[p].ch[s[siz]] = cnt;
        }
        lst = node[p].ch[s[siz]];
    }
};

class Solution : public PAM {
   private:
    char d[MAX_N];

   public:
    void solve() {
        std::cin >> (d + 1);
        len = std::strlen(d + 1);

        int last_ans = 0;
        s[0] = '$';

        for (siz = 1; siz <= len; siz++) {
            d[siz] = (d[siz] - 97 + last_ans) % 26 + 97;
            s[siz] = d[siz] - 'a';
            build();

            last_ans = node[lst].num;
            std::cout << last_ans << ' ';
        }
    }
};

int main() {
    std::ios::sync_with_stdio(false);

    Solution* soulution = new Solution();
    soulution->solve();
    delete soulution;

    return 0;
}