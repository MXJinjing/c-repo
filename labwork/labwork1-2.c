/*
    һ�Ѻ�����m������ŷֱ���1��2��3 ...m����m�����Ӱ��ձ��1,2,��,m��˳��Χ��һȦ��
    Ȼ��ӵ�1��ʼ����ÿ������n�����ú��Ӿ�Ҫ�뿪��Ȧ����������������
    ֱ��Ȧ��ֻʣ�����һֻ���ӣ���ú��Ӿ�Ϊ������

    Ҫ�󣺷ֱ�����������������ִ洢��ʽʵ�ָ��������⣬����һ��m��n�������Ӧ�ĺ�����
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
    printf("������\n������m,n:\n");
    scanf("%d %d", &m, &n);
    if (m < 1 || n < 1)
    {
        printf("���ݴ���");
        return 0;
    }

    //����ͷ�ڵ�
    head = malloc(sizeof(mk));
    head->ID = 1;
    head->Next = NULL;

    //����ʣ��ڵ�
    p = head;
    for (int i = 0; i < m - 1; i++)
    {
        q = malloc(sizeof(mk));
        q->ID = i + 2;
        q->Next = NULL;
        p->Next = q, p = q;
    }
    //����ѭ��
    q->Next = head, r = q = head, p = q->Next;
    while (1)
    {
        //�ƶ�ָ��
        for (int i = 0; i < n - 1; i++)
        {
            r = q, q = p, p = p->Next;
        }
        if (q->Next == q)
            break;
        printf("��%dֻ�����뿪��\n", q->ID);
        fprintf(file, "%d", q->ID);
            //ɾ���ڵ�
            r->Next = p;
        q = r = p;
        p = p->Next;
    }
    fprintf(file, "%d", q->ID);
    printf("��%dֻ����Ϊ��\n", q->ID);
    fclose(file);
    return 0;
}