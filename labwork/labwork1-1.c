/*
    һ�Ѻ�����m������ŷֱ���1��2��3 ...m����m�����Ӱ��ձ��1,2,��,m��˳��Χ��һȦ��
    Ȼ��ӵ�1��ʼ����ÿ������n�����ú��Ӿ�Ҫ�뿪��Ȧ����������������
    ֱ��Ȧ��ֻʣ�����һֻ���ӣ���ú��Ӿ�Ϊ������

    Ҫ�󣺷ֱ�����������������ִ洢��ʽʵ�ָ��������⣬����һ��m��n�������Ӧ�ĺ�����
*/

#include <stdio.h>
#include <stdlib.h>

int main()
{
    FILE *f = fopen("labwork1-1-output.txt", "w");
    int m, n;
    printf("������\n������m,n:\n");
    scanf("%d%d", &m, &n);
    int monkey[99];
    int i, m_, count, q, win;
    for (i = 0; i < m; i++)
        monkey[i] = 0; //�涨���к��Ӷ���
    m_ = 0;            //�ߵ��ĺ�������
    count = 0, q = 0;
    while (m_ < m) //���ƴ���
    {
        if (count == n - 1) //�������
        {
            while (monkey[q] != 0) //���Ӹպò���������һ��
                if (++q == m)
                    q = 0;
            win = q + 1;
            if (m_ < m - 1)
                printf("��%dֻ�����뿪��\n", win);
            fprintf(f, "%d", q + 1);
            monkey[q] = 1;
            m_++;
            count = 0; //���ü���
        }
        else if (monkey[q] == 0) //����δ���
            count++;             //�������δ�뿪�����
        q++;
        if (q == m) //����ѭ������
            q = 0;
    }
    printf("��%dֻ����Ϊ��\n", win);
    fclose(f);
    return 0;
}
