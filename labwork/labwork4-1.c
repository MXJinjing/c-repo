/*
    �θ�һ��Ӣ�����ϵ��ı��ļ���Ҫ����������¹��ܣ�ͳ�Ƹ��ı��ļ������е���(ÿ�����ʲ������ո񼰿��У�
    ��������ĸ���й����Ҳ����ִ�Сд���������ֵ�˳�����д洢��һ���ļ��ͳ��ÿ���������ı��ļ��г��ֵ��ܴ�����
    Ƶ�ȣ��õ��ʳ��ֵ��ܴ���/���е��ʳ��ִ���֮�ͣ������ı��ļ����״γ��ֵ��кż�λ�á�
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void TransCapital(char *in, char *out) //����ת����дΪСд
{
    int i = 0, j = 0;
    while (*(in + i) != '\0')
    {
        char ch = *(in + i);
        if (ch >= 'A' && ch <= 'Z')
            ch += 32;
        *(out + j) = ch;
        i++;
        j++;
    }
    *(out + j) = '\0';
}

typedef struct node
{
    char s[50];
    int row;
    int col;
    int times;
    struct node *next;
} word;

int main()
{
    FILE *t = fopen("labwork4-1-temp.txt", "w"); //�򿪻����ļ�
    FILE *p = fopen("labwork4-1-read.txt", "r"); //�������ļ�

    word *head[26], *lead, *follow;
    for (int i_ = 0; i_ < 26; i_++)
    {
        head[i_] = (word *)malloc(sizeof(word)); //Ϊ��ͷ�ڵ����ռ�
        head[i_]->next = NULL;
    }

    char ch;
    char temp[50];
    int i, col = 1, row = 0;
    while ((ch = fgetc(p)) != EOF) //���ֶ�ȡ�ļ�
    {
        if (ch == '\n') //���У���������
            col++, row = 0;
        if ((ch <= 'Z' && ch >= 'A') || (ch <= 'z' && ch >= 'a')) //�������Ӣ���ַ������¼�õ���
        {
            i = 0, row++;
            while ((ch <= 'Z' && ch >= 'A') || (ch <= 'z' && ch >= 'a') || (ch == '-' && temp[i - 1] != '-') || (ch == '\''))
            {
                temp[i] = ch;
                ch = fgetc(p);
                i++;
            }
            if (temp[i - 1] == '-' || temp[i - 1] == '\'')
                i--;
            temp[i] = '\0';

            //������ʱ�ڵ�
            word *tempnode = (word *)malloc(1*sizeof(word));
            TransCapital(temp, tempnode->s); //ת����дΪСд
            tempnode->times = 1;
            tempnode->col = col;
            tempnode->row = row;
            tempnode->next = NULL;

            fprintf(t,"%s-- ",tempnode->s);
            fprintf(t, "putting \"%s\" to head[%d]\n", tempnode->s, tempnode->s[0] - 97);

            //�����ʼ�������
            lead = head[tempnode->s[0] - 97]->next, follow = head[tempnode->s[0] - 97];
            while (lead != NULL)
            {
                fprintf(t, "lead = %s\t temp = %s\n", lead->s, tempnode->s);
                if (strcmp(lead->s, tempnode->s) == 0) //��������ظ��ĵ���
                {
                    lead->times++;
                    fprintf(t, "Done: times ++\n\n");
                    break;
                }
                if (strcmp(lead->s, tempnode->s) > 0 && (strcmp(follow->s, tempnode->s) < 0 || follow == head[tempnode->s[0] - 97]))
                //������ʵ�˳��Ӧ������ǰ�����м�
                {
                    tempnode->next = lead;
                    follow->next = tempnode;
                    if (follow != head[tempnode->s[0] - 97])
                        fprintf(t, "Done: put in the middle of \"%s\" and \"%s\"\n\n", follow->s, lead->s);
                    else
                        fprintf(t, "Done: put in the middle of head and \"%s\"\n\n", lead->s);
                    break;
                }
                follow = lead, lead = lead->next;
            }
            if (lead == NULL) //������ʵ�˳�������
            {
                fprintf(t, "Done: put in the tail\n\n");
                follow->next = tempnode;
            }
        }
    }
    //ͳ���ܴ���
    int total = 0;
    for (int i_ = 0; i_ < 26; i_++)
    {
       lead = head[i_]->next;
        while (lead != NULL)
        {
            total++;
            lead = lead->next;
        }
    }

    //������
    FILE *p2 = fopen("labwork4-1-out.md", "w"); //������ļ�
    fprintf(p2, "|���|����|����|��|��|Ƶ��|\n|-|---|--|--|--|--|\n");
    i = 1;
    for (int i_ = 0; i_ < 26 ; i_++)
    {
        lead = head[i_]->next;
        double t2 = (double)total; //ת��������
        while (lead != NULL)
        {
            double t1 = (double)lead->times; //ת��������
            fprintf(p2, "|%2d|%s|%d|%d|%d|%f|\n", i, lead->s, lead->times, lead->col, lead->row, t1 / t2);
            lead = lead->next;
            i++;
        }
    }
    //�ر��ļ�
    fclose(p);
    fclose(p2);
    fclose(t);
    return 0;
}
