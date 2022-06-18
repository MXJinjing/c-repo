/*
    一堆猴子有m个，编号分别是1，2，3 ...m，这m个猴子按照编号1,2,…,m的顺序围坐一圈，
    然后从第1开始数，每数到第n个，该猴子就要离开此圈，这样依次下来，
    直到圈中只剩下最后一只猴子，则该猴子就为大王。
    
    要求：分别采用向量及链表两种存储方式实现该问题的求解，给出一组m和n，输出对应的猴王。
*/

#include <stdio.h>
#include <stdlib.h>

int main()
{
    printf("title\n");
    int m, n;
    printf("向量求法\n请输入m,n:\n");
    scanf("%d%d", &m, &n);
    int monkey[99];
    int i, m_, count, q;

    for (i = 0; i < m; i++)
        monkey[i] = 0; //规定所有猴子都在

    m_ = 0;
    count = 0, q = 0;
    while (m_ != m - 1) //限制次数
    {
        if (count == n - 1) //计数完成
        {
            while (monkey[q] != 0) //猴子刚好不在则往后一个
            {
                q++;
                if (q == m)
                    q = 0;
            }
            printf("第%d只猴子离开了\n", q + 1);
            monkey[q] = 1;
            m_++;
            count = 0; //重置计数
        }
        else //计数未完成
        {
            if (monkey[q] == 0)
                count++; //如果猴子未离开则计数
        }
        q++;
        if (q == m)
            q = 0;
    }

    for (i = 0; i < m; i++) //寻找猴王
        if (monkey[i] == 0)
            printf("第%d只猴子为王\n", i + 1);
    return 0;
}
