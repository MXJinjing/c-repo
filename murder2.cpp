#include <bits/stdc++.h>
using namespace std;
const int MAXN = 3e5 + 20;

int maxL[MAXN];
struct Aho_Corasick {
    struct Node {
        int len;
        Node *ch[26], *fail;
        Node()
        {
            len = 0, fail = nullptr;
            for (int i = 0; i < 26; ++i)
                ch[i] = nullptr;
        }
    };
    Node* root;
    Aho_Corasick() { root = new Node; }
    inline void insert(const string& s)
    {
        Node* u = root;
        for (auto p : s) {
            if (u->ch[p - 'a'] == nullptr) {
                u->ch[p - 'a'] = new Node;
            }
            u = u->ch[p - 'a'];
        }
        u->len = s.size();
    }
    inline void build()
    {
        Node* u = root;
        queue<Node*> que;
        u->fail = root;
        for (int i = 0; i < 26; ++i) {
            if (u->ch[i] != nullptr) {
                u->ch[i]->fail = root;
                que.push(u->ch[i]);
            } else {
                u->ch[i] = root;
            }
        }
        while (!que.empty()) {
            u = que.front();
            que.pop();
            u->len = max(u->len, u->fail->len);
            for (int i = 0; i < 26; ++i) {
                if (u->ch[i] == nullptr) {
                    u->ch[i] = u->fail->ch[i];
                } else {
                    que.push(u->ch[i]);
                    u->ch[i]->fail = u->fail->ch[i];
                }
            }
        }
    }
    inline void calc(const string& s)
    {
        Node* u = root;
        for (int i = 1; i <= s.size(); ++i) {
            u = u->ch[s[i - 1] - 'a'];
            maxL[i] = u->len;
        }
    }
} aca;
int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    int L;
    cin >> L;
    string s;
    cin >> s;
    while (L--) {
        string t;
        cin >> t;
        aca.insert(t);
    }
    aca.build();
    aca.calc(s);
    priority_queue<pair<int, int>, vector<pair<int, int>>,
        greater<pair<int, int>>>
        dp;
    int n = s.size();
    dp.push(pair<int, int>(0, n));
    int ans = n;
    for (int i = n; i >= 1; --i) {
        int dpi = -1;
        while (!dp.empty()) {
            if (dp.top().second > i)
                dp.pop();
            else {
                dpi = dp.top().first;
                break;
            }
        }
        if (dpi == -1) {
            cout << -1 << endl;
            return 0;
        }
        if (maxL[i] != 0) {
            dp.push(pair<int, int>(dpi + 1, i - maxL[i]));
            if (i == maxL[i])
                ans = min(ans, dpi + 1);
        }
    }
    cout << ans << endl;
    return 0;
}