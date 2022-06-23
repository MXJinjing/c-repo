/*
    ��������һԪ����ʽA(x),B(x)�����������A(x)+B(x)��A(x)-B(x)��Ҫ�����ʽ��������ṹ���д洢��
    ����ʽ���԰������ݣ����ݣ���ʽ�����Ӧ��ϵ����ָ����������������ʽ����Ҫ��

    ��չ���⣺
    (1)һԪ����ʽ�ĳ˷����㣬���ʵ�֣�
    (2)һԪ����ʽ�ĳ������㣬���ʵ�֣�
    (3)��Ԫ����ʽ�ļӷ������ʵ�֣�
*/

#include <math.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct polynomial
{
    double coef; //ϵ��
    int index;   //ָ��
    struct polynomial *next;
} pol;

void pol_record(pol *head, double coef, int index, int mod) //�����ݼ�¼����ʽ
{
    pol *lead, *follow, *p;
    p = (pol *)malloc(sizeof(pol));
    p->next = NULL;
    p->coef = coef;
    p->index = index;

    if (p->index < 0) //���ָ����Χ
    {
        printf("error:ָ������Ϊ��\n");
        return;
    }

    lead = follow = head;
    while (1)
    {
        follow = lead;
        lead = lead->next;
        if (lead == NULL) //��β����������
        {
            follow->next = p;
            break;
        }
        if (lead->index == p->index) //��ƥ�䵽��ָͬ��
        {
            if (mod == 1) //�ӷ�ģʽ
                p->coef += lead->coef;
            lead->coef = p->coef;
            break;
        }
        if ((lead->index < p->index && follow->index > p->index) || (lead->index < p->index && follow == head)) //��ͷ�����м����
        {
            follow->next = p;
            p->next = lead;
            break;
        }
    }
    follow = head;
    lead = follow->next;
    while (lead != NULL) //�Զ�ɾ������0
    {
        if (lead->coef == 0) //��ƥ�䵽ϵ��Ϊ0
            follow->next = lead->next;
        follow = lead;
        lead = lead->next;
    }
    lead = head->next;
    if (lead == NULL) //û�����������ȥʱΪ0
    {
        pol *temp;
        temp = (pol *)malloc(sizeof(pol));
        temp->next = NULL;
        temp->coef = 0;
        temp->index = 0;
        head->next = temp;
    }
    return;
}

void pol_print(pol *head)
{
    pol *lead, *follow;
    lead = follow = head->next;
    if (lead == NULL) //������ʽ�Ƿ����
    {
        printf("error:����ʽ������\n");
        return;
    }
    while (lead != NULL) //��ӡ����ʽ
    {
        follow = lead;
        lead = lead->next;
        //��ӡ����

        if (!(follow->index == 0 || follow->index == 1 || follow->index == -1))
            if (follow->coef == 1)
                printf("x^%d", follow->index);
            else
                printf("%.2gx^%d", follow->coef, follow->index);
        else
        {
            if (follow->index == 0)
                printf("%.2g", follow->coef);
            if (follow->index == 1)
                if (follow->coef == 1)
                    printf("x");
                else
                {
                    if (follow->coef == -1)
                        printf("-x");
                    else
                        printf("%.2gx", follow->coef);
                }
        }
        if (lead != NULL)
        {
            if (lead->coef >= 0)
                printf("+");
        }
    }
}

void pol_print_file(pol *head, FILE *p)
{
    pol *lead, *follow;
    lead = follow = head->next;
    if (lead == NULL) //������ʽ�Ƿ����
    {
        printf("error:����ʽ������\n");
        return;
    }
    while (lead != NULL) //��ӡ����ʽ
    {
        follow = lead;
        lead = lead->next;
        //��ӡ����

        if (!(follow->index == 0 || follow->index == 1 || follow->index == -1))
            if (follow->coef == 1)
            {
                fprintf(p, "x^%d", follow->index);
            }
            else
            {
                fprintf(p, "%.2gx^%d", follow->coef, follow->index);
            }
        else
        {
            if (follow->index == 0)
            {
                fprintf(p, "%.2g", follow->coef);
            }
            if (follow->index == 1)
                if (follow->coef == 1)
                {
                    fprintf(p, "x");
                }
                else
                {
                    if (follow->coef == -1)
                    {
                        fprintf(p, "-x");
                    }

                    else
                    {
                        fprintf(p, "%.2gx", follow->coef);
                    }
                }
        }
        if (lead != NULL)
        {
            if (lead->coef >= 0)
            {
                fprintf(p, "+");
            }
        }
    }
}

pol *cal_and(pol *A, pol *B)
{
    if (A->next == NULL)
        printf("error:����ʽA������\n");
    if (B->next == NULL)
        printf("error:����ʽB������\n");

    pol *AND, *pA, *pB, *p, *follow, *lead, *temp;
    AND = (pol *)malloc(sizeof(pol));
    AND->next = NULL;
    p = follow = AND;
    pA = A;
    while (pA != NULL) //����A��AND
    {
        if (p == NULL)
        {
            p = (pol *)malloc(sizeof(pol));
            p->coef = pA->coef;
            p->index = pA->index;
            p->next = NULL;
            follow->next = p;
        }
        follow = p;
        p = p->next;
        pA = pA->next;
    }
    pB = B->next;
    while (pB != NULL) //����B��AND
    {
        pol_record(AND, pB->coef, pB->index, 1);
        pB = pB->next;
    }
    follow = lead = AND;
    follow = lead;
    lead = lead->next;
    if (lead == NULL) //û�����������ȥʱΪ0
    {
        temp = (pol *)malloc(sizeof(pol));
        follow->next = temp;
        temp->next = lead;
        follow = follow->next;
        follow->coef = 0;
        follow->index = 0;
    }
    return AND;
}

pol *cal_and3(pol *A, pol *B, pol *C)
{
    pol *temp = (pol *)malloc(sizeof(pol));
    temp = cal_and(A, B);
    temp = cal_and(temp, C);
    return temp;
}

int main()
{
    FILE *p = fopen("labwork2-2-out.txt", "w");
    pol *A, *B, *C, *AND;
    int index;
    char choice;
    double coef;
    choice = 'n';
    A = (pol *)malloc(sizeof(pol));
    A->next = NULL;
    B = (pol *)malloc(sizeof(pol));
    B->next = NULL;
    C = (pol *)malloc(sizeof(pol));
    C->next = NULL;

    printf("--------------------�����������ʽ A-------------------- \n\n");
    while (1)
    {
        printf("������ϵ��&ָ����");
        scanf("%lf%d", &coef, &index);
        pol_record(A, coef, index, 0);
        pol_print(A);
        printf("\n");
        printf("������(�س�����������n�˳�):");
        getchar();
        scanf("%c", &choice);
        if (choice == 'n')
            break;
    }
    printf("\n--------------------�����������ʽ B-------------------- \n\n");
    while (1)
    {
        printf("������ϵ��&ָ����");
        scanf("%lf%d", &coef, &index);
        pol_record(B, coef, index, 0);
        pol_print(B);
        printf("\n");
        printf("������(�س�����������n�˳�):");
        getchar();
        scanf("%c", &choice);
        if (choice == 'n')
            break;
    }
    printf("\n--------------------�����������ʽ C-------------------- \n\n");
    while (1)
    {
        printf("������ϵ��&ָ����");
        scanf("%lf%d", &coef, &index);
        pol_record(C, coef, index, 0);
        pol_print(C);
        printf("\n");
        printf("������(�س�����������n�˳�):");
        getchar();
        scanf("%c", &choice);
        if (choice == 'n')
            break;
    }

    AND = cal_and3(A, B, C);
    printf("\t");
    pol_print(A);
    printf("\n");
    printf("\t");
    pol_print(B);
    printf("\n");
    printf("+");
    printf("\t");
    pol_print(C);
    printf("\n");
    printf("----------------------------------------------------------\n");
    printf("\t");
    pol_print(AND);
    pol_print_file(AND, p);
    printf("\n");
    fclose(p);
    return 0;
}
