#include <bits/stdc++.h>
using namespace std;
typedef long ll;
typedef pair<int, int> pii;
typedef pair<ll, ll> pll;

int n, q;
int dp[500][500]; // dp[u][j] 表示在以 u 为根的子树保留 j 个分支可以得到的最大苹果数量
struct edge
{
    int v, w, next;
} e[500];

int head[500], cnt;

void dfs(int u, int fa)
{
    for (int i = head[u]; ~i; i = e[i].next)
    {
        int v = e[i].v;
        if (v == fa)
            continue;
        dfs(v, u);
        for (int j = q; j >= 1; j--)
        {
            for (int k = 1; k <= j; k++) // 在 v 节点的子树中选择 k 条边
            {
                dp[u][j] = max(dp[u][j], dp[u][j - k] + dp[v][k - 1] + e[i].w);
            }
        }
    }
}
int main()
{
#ifdef LZH_LOCAL
    freopen("in.in", "r", stdin);
    // freopen("out.out", "w", stdout);
#endif
    ios::sync_with_stdio(0), cin.tie(0), cout.tie(0);
    memset(head, -1, sizeof(head));
    cin >> n >> q;
    for (int i = 1; i < n; i++)
    {
        int u, v, w;
        cin >> u >> v >> w;
        e[cnt] = {v, w, head[u]};
        head[u] = cnt++;
        e[cnt] = {u, w, head[v]};
        head[v] = cnt++;
    }
    dfs(1, 0);
    cout << dp[1][q] << endl;
    return 0;
}
