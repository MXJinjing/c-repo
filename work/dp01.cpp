/*
    最长上升子序列
    f(i) = max(f(x) + 1), x>i,f(x) > f(i)
*/

#include <algorithm>
#include <stdio.h>
using namespace std;

int n, a[1000],f[1000], answer;

int main()
{
    scanf("%d", &n);
    for (int i = 0; i < n; i++)
        scanf("%d", &a[i]);
    for (int i = 0; i < n; i++) {
        f[i] = 1;
        for (int x = 0; x < i; x++)
            if (a[x] < a[i])
                f[i] = max(f[x]+1,f[i]);
        printf("f[%d] = %d\n", i, f[i]);
    }

    for (int i = 0; i < n; i++){
        answer = max(answer,f[i]);
    }

    printf("answer = %d",answer);

    return 0;
}