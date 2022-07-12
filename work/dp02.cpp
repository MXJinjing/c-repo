
/*
    输入格式:
    第一行两个数 n 和 q ，n 表示树的节点数，q 表示要保留的树枝数量。
    接下来 n 行描述树枝信息，每行三个整数，前两个是它连接的节点的编号，第三个数是这根树枝上苹果数量。
    输出格式:
    输出仅一行，表示最多能留住的苹果的数量。
    输入样例:
    5 2
    1 3 1
    1 4 10
    2 3 20
    3 5 2
*/
#include <algorithm>
#include <stdio.h>
#define MAXN 1000
using namespace std;

int q, n, id, father, edge, top;
int tree[MAXN][2]; // lson and rson
int value[MAXN]; // value of edge
int idused[MAXN]; // used for id
int dp[MAXN][MAXN];
int stack[MAXN];

void buildTree();
int dfs(int root, int q);

int main()
{
    scanf("%d %d", &n, &q);
    edge = n - 1;
    buildTree();
    printf("%d", dfs(1, q));
    return 0;
}

int dfs(int root, int q)
{
    if (dp[root][q] != 0)
        return dp[root][q];
    if ()
        
    for (int j = q; j >= 1; j--) {
        for (int i = 1; i <= q; i++) {
            int left = dfs(tree[root][0], q - i);
            int right = dfs(tree[root][1], i - 1);
            dp[root][q]
                = max(dp[root][q], dp[tree[root][0]][q - i] + dp[tree[root][1]][i - 1] + value[root]);
        }
    }
    printf("dp[%d][%d] = %d\n", root, q, dp[root][q]);
    return dp[root][q];
}

void buildTree()
{
    for (int i = 0; i < MAXN; i++) {
        for (int j = 0; j < MAXN; j++) {
            if (j < 2)
                tree[i][j] = -1;
            dp[i][j] = 0;
        }
        value[i] = 0;
        idused[i] = -1;
    }
    int v, u, temp;
    tree[1][1] = tree[1][1] = -1;
    idused[1] = 0;
    for (int i = 0; i < edge; i++) {
        scanf("%d %d %d", &u, &v, &temp);
        if (idused[u] < 2 && idused[v] == -1) {
            father = u, id = v, idused[father]++, idused[id]++;
        } else if (idused[v] < 2 && idused[u] == -1) {
            father = v, id = u, idused[father]++, idused[id]++;
        }
        value[id] = temp;
        if (tree[father][0] == -1) {
            tree[father][0] = id;
        } else if (tree[father][1] == -1) {
            tree[father][1] = id;
        }
    }
    return;
}