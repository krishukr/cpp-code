#include <cstring>
#include <iostream>

int vis[30];

int main() {
    freopen("dilute.in", "r", stdin);
    freopen("dilute.out", "w", stdout);

    std::string s, stk;
    std::cin >> s;
    char min = s[0];
    int m = 0, p = -1;

    for (int i = 0; i < s.size(); i++) {
        vis[s[i] - 'a']++;
    }

    for (int i = 0; i < s.size(); i++) {
        if (!vis[s[i] - 'a']) {
            continue;
        }
        if (min > s[i]) {
            min = s[i];
            m = i;
        }
        if (i < p) {
            continue;
        }
        if (vis[s[i] - 'a'] == 1) {
            stk.push_back(min);
            vis[min - 'a'] = 0;
            p = i;
            i = m;
            min = 123;
        } else {
            vis[s[i] - 'a']--;
        }
    }

    std::cout << stk << '\n';

    fclose(stdin);
    fclose(stdout);
    return 0;
}
