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

typedef struct pol_with_leave
{
    pol *main;
    pol *leave_num;
    pol *leave_den;
} pol3;

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
        if ((lead->index < p->index && follow->index > p->index) ||
            (lead->index < p->index && follow == head)) //��ͷ�����м����
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
    FILE *p = fopen("labwork2-1-out.txt", "a");
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
                printf("x^%d", follow->index);
            }
            else
            {
                printf("%.2gx^%d", follow->coef, follow->index);
            }
        else
        {
            if (follow->index == 0)
            {
                printf("%.2g", follow->coef);
            }
            if (follow->index == 1)
                if (follow->coef == 1)
                {
                    printf("x");
                }

                else
                {
                    if (follow->coef == -1)
                    {
                        printf("-x");
                    }

                    else
                    {
                        printf("%.2gx", follow->coef);
                    }
                }
        }
        if (lead != NULL)
        {
            if (lead->coef >= 0)
            {
                printf("+");
            }
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
    return;
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

pol *cal_sub(pol *A, pol *B)
{
    if (A->next == NULL)
        printf("error:����ʽA������\n");
    if (B->next == NULL)
        printf("error:����ʽB������\n");
    pol *pB, *B_, *p, *follow, *sub;
    pB = B;

    //�Ƚ�B��ϵ��ȡ�෴��
    B_ = (pol *)malloc(sizeof(pol));
    B_->next = NULL;
    p = follow = B_;
    while (pB != NULL) //����-B
    {
        if (p == NULL)
        {
            p = (pol *)malloc(sizeof(pol));
            p->coef = -1. * pB->coef;
            p->index = pB->index;
            p->next = NULL;
            follow->next = p;
        }
        follow = p;
        p = p->next;
        pB = pB->next;
    }
    sub = cal_and(A, B_);
    return sub;
}

pol *cal_mul(pol *A, pol *B)
{
    pol *MUL, *follow, *lead, *pA, *pB;
    int tempi;
    double tempc;
    pA = A->next;
    pB = B->next;
    MUL = (pol *)malloc(sizeof(pol));
    MUL->next = NULL;
    while (pA != NULL)
    {
        pB = B->next;
        while (pB != NULL)
        {
            tempc = pA->coef * pB->coef;   //ϵ�����
            tempi = pA->index + pB->index; //ָ�����
            pol_record(MUL, tempc, tempi, 1);
            pB = pB->next;
        }
        pA = pA->next;
    }
    return MUL;
}

pol3 *cal_div(pol *A, pol *B)
{
    pol *A_, *pA, *pB, *DIV, *p, *temp, *follow, *lead, *temp2, *B_, *ptemp;
    pol3 *ANSWER;
    ANSWER = (pol3 *)malloc(sizeof(pol3));
    DIV = (pol *)malloc(sizeof(pol));
    DIV->next = NULL;
    A_ = (pol *)malloc(sizeof(pol));
    A_->next = NULL;
    p = follow = A_;
    pA = A;
    while (pA != NULL) //����A��A_
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

    B_ = (pol *)malloc(sizeof(pol));
    B_->next = NULL;
    p = follow = B_;
    pB = B;
    while (pB != NULL) //����B��B_
    {
        if (p == NULL)
        {
            p = (pol *)malloc(sizeof(pol));
            p->coef = pB->coef;
            p->index = pB->index;
            p->next = NULL;
            follow->next = p;
        }
        follow = p;
        p = p->next;
        pB = pB->next;
    }

    int tempi, tempi2, Aimin, Bimin, imin;
    double tempc, tempc2;
    pB = B_->next;
    pA = A_->next;
    int Bimax = pB->index;   // B����ߴ���
    double Bcmax = pB->coef; // B����ߴ�����ϵ��
    if (pA->index < Bimax)   //���û��A�Ĵ���С��B
    {
        ANSWER->main = (pol *)malloc(sizeof(pol));
        ANSWER->main->next = NULL;
        pol_record(ANSWER->main, 0, 0, 0);
        goto mark;
    }
    while ((A_->next != NULL && pA->index >= Bimax)) //���A�Ĵ�������B
    {
        //��¼������
        tempc = pA->coef / Bcmax;
        tempi = pA->index - Bimax;
        pol_record(DIV, tempc, tempi, 1);

        //��¼������temp
        temp = (pol *)malloc(sizeof(pol));
        temp->next = NULL;

        lead = (pol *)malloc(sizeof(pol));
        ;
        lead->coef = tempc;
        lead->index = tempi;
        lead->next = NULL;
        temp->next = lead;

        // A_��ȥ�����temp2
        ptemp = temp->next;
        pB = B_->next;
        lead = follow = temp;
        lead = lead->next;
        temp2 = cal_mul(B_, temp);

        A_ = cal_sub(A_, temp2);
        pA = A_->next;
    }
    ANSWER->main = DIV;
    pA = A_->next;
mark:
    //�����С�Ĵ���
    for (lead = A_; lead != NULL; lead = lead->next)
        Aimin = lead->index;
    for (lead = B_; lead != NULL; lead = lead->next)
        Bimin = lead->index;
    if (Aimin > Bimin)
        imin = Bimin;
    else
        imin = Aimin;
    //Լȥ�����x
    if (imin != 0)
    {
        for (lead = A_->next; lead != NULL; lead = lead->next)
            lead->index -= imin;
        for (lead = B_->next; lead != NULL; lead = lead->next)
            lead->index -= imin;
    }
    if (A_->next->coef == 0 && A_->next->index == 0)
    {
        ANSWER->leave_den = NULL;
        ANSWER->leave_num = NULL;
    }
    else
    {
        ANSWER->leave_num = A_;
        ANSWER->leave_den = B_;
    }
    return ANSWER;
}

int main()
{
    FILE *p = fopen("labwork2-1-out.txt", "a");
    pol *A, *B, *AND, *SUB, *MUL, *leave;
    pol3 *ANSWER;
    char choice;
    int index;
    double coef;
    choice = 'n';
    A = (pol *)malloc(sizeof(pol));
    A->next = NULL;
    B = (pol *)malloc(sizeof(pol));
    B->next = NULL;

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
    printf("\n");
    AND = cal_and(A, B);
    printf("\t");
    pol_print(A);
    printf("\n");
    printf("+");
    printf("\t");
    pol_print(B);
    printf("\n");
    printf("----------------------------------------------------------\n");
    printf("\t");
    pol_print(AND);
    pol_print_file(AND, p);
    fprintf(p, "\n");
    printf("\n\n");

    SUB = cal_sub(A, B);
    printf("\t");
    pol_print(A);
    printf("\n");
    printf("-");
    printf("\t");
    pol_print(B);
    printf("\n");
    printf("----------------------------------------------------------\n");
    printf("\t");
    pol_print(SUB);
    pol_print_file(SUB, p);
    fprintf(p, "\n");
    printf("\n\n");

    MUL = cal_mul(A, B);
    printf("\t");
    pol_print(A);
    printf("\n");
    printf("*");
    printf("\t");
    pol_print(B);
    printf("\n");
    printf("----------------------------------------------------------\n");
    printf("\t");
    pol_print(MUL);
    pol_print_file(MUL, p);
    fprintf(p, "\n");
    printf("\n\n");

    ANSWER = cal_div(A, B);
    printf("\t");
    pol_print(A);
    printf("\n");
    printf("/");
    printf("\t");
    pol_print(B);
    printf("\n");
    printf("----------------------------------------------------------\n");
    printf("\t");
    if (!(ANSWER->main->next->index == 0 && ANSWER->main->next->coef == 0))
    {
        pol_print(ANSWER->main);
        pol_print_file(ANSWER->main, p);
    }
    if (!(ANSWER->main->next->index == 0 && ANSWER->main->next->coef == 0) &&
        (ANSWER->leave_den != NULL))
    {
        fprintf(p, "+");
        printf("+");
    }
    if (ANSWER->leave_den != NULL)
    {
        printf("(");
        fprintf(p, "(");
        pol_print(ANSWER->leave_num);
        pol_print_file(ANSWER->leave_num, p);
        printf(")/(");
        fprintf(p,  ")/(");
        pol_print(ANSWER->leave_den);
        pol_print_file(ANSWER->leave_den, p);
        printf(")");
        fprintf(p, ")");
    }
    fprintf(p, "\n");
    printf("\n\n");
    fclose(p);
    return 0;
}
