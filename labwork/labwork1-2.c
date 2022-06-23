/*
    一堆猴子有m个，编号分别是1，2，3 ...m，这m个猴子按照编号1,2,…,m的顺序围坐一圈，
    然后从第1开始数，每数到第n个，该猴子就要离开此圈，这样依次下来，
    直到圈中只剩下最后一只猴子，则该猴子就为大王。

    要求：分别采用向量及链表两种存储方式实现该问题的求解，给出一组m和n，输出对应的猴王。
*/

#include <stdio.h>
#include <stdlib.h>

typedef struct node
{
    int ID;
    struct node *Next;
} mk;

int main()
{
    FILE *file = fopen("labwork1-2-output.txt", "w");
    mk *head, *q, *p, *r;
    int m, n;
    printf("链表求法\n请输入m,n:\n");
    scanf("%d %d", &m, &n);
    if (m < 1 || n < 1)
    {
        printf("数据错误");
        return 0;
    }

    //创建头节点
    head = malloc(sizeof(mk));
    head->ID = 1;
    head->Next = NULL;

    //创建剩余节点
    p = head;
    for (int i = 0; i < m - 1; i++)
    {
        q = malloc(sizeof(mk));
        q->ID = i + 2;
        q->Next = NULL;
        p->Next = q, p = q;
    }
    //构建循环
    q->Next = head, r = q = head, p = q->Next;
    while (1)
    {
        //移动指针
        for (int i = 0; i < n - 1; i++)
        {
            r = q, q = p, p = p->Next;
        }
        if (q->Next == q)
            break;
        printf("第%d只猴子离开了\n", q->ID);
        fprintf(file, "%d", q->ID);
            //删除节点
            r->Next = p;
        q = r = p;
        p = p->Next;
    }
    fprintf(file, "%d", q->ID);
    printf("第%d只猴子为王\n", q->ID);
    fclose(file);
    return 0;
}