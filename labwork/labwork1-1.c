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
    FILE *f = fopen("labwork1-1-output.txt", "w");
    int m, n;
    printf("向量求法\n请输入m,n:\n");
    scanf("%d%d", &m, &n);
    int monkey[99];
    int i, m_, count, q, win;
    for (i = 0; i < m; i++)
        monkey[i] = 0; //规定所有猴子都在
    m_ = 0;            //走掉的猴子数量
    count = 0, q = 0;
    while (m_ < m) //限制次数
    {
        if (count == n - 1) //计数完成
        {
            while (monkey[q] != 0) //猴子刚好不在则往后一个
                if (++q == m)
                    q = 0;
            win = q + 1;
            if (m_ < m - 1)
                printf("第%d只猴子离开了\n", win);
            fprintf(f, "%d", q + 1);
            monkey[q] = 1;
            m_++;
            count = 0; //重置计数
        }
        else if (monkey[q] == 0) //计数未完成
            count++;             //如果猴子未离开则计数
        q++;
        if (q == m) //构建循环数组
            q = 0;
    }
    printf("第%d只猴子为王\n", win);
    fclose(f);
    return 0;
}
