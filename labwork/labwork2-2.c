/*
    设有两个一元多项式A(x),B(x)，请完成运算A(x)+B(x)、A(x)-B(x)，要求多项式采用链表结构进行存储，
    多项式可以按照升幂（降幂）形式输入对应的系数、指数项，但对输入输出格式不做要求。

    扩展问题：
    (1)一元多项式的乘法运算，如何实现？
    (2)一元多项式的除法运算，如何实现？
    (3)多元多项式的加法，如何实现？
*/

#include <math.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct polynomial
{
    double coef; //系数
    int index;   //指数
    struct polynomial *next;
} pol;

void pol_record(pol *head, double coef, int index, int mod) //按降幂记录多项式
{
    pol *lead, *follow, *p;
    p = (pol *)malloc(sizeof(pol));
    p->next = NULL;
    p->coef = coef;
    p->index = index;

    if (p->index < 0) //检查指数范围
    {
        printf("error:指数不能为负\n");
        return;
    }

    lead = follow = head;
    while (1)
    {
        follow = lead;
        lead = lead->next;
        if (lead == NULL) //在尾部插入新项
        {
            follow->next = p;
            break;
        }
        if (lead->index == p->index) //当匹配到相同指数
        {
            if (mod == 1) //加法模式
                p->coef += lead->coef;
            lead->coef = p->coef;
            break;
        }
        if ((lead->index < p->index && follow->index > p->index) || (lead->index < p->index && follow == head)) //在头或者中间插入
        {
            follow->next = p;
            p->next = lead;
            break;
        }
    }
    follow = head;
    lead = follow->next;
    while (lead != NULL) //自动删除多余0
    {
        if (lead->coef == 0) //当匹配到系数为0
            follow->next = lead->next;
        follow = lead;
        lead = lead->next;
    }
    lead = head->next;
    if (lead == NULL) //没有项即所有项消去时为0
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
    if (lead == NULL) //检测多项式是否存在
    {
        printf("error:多项式不存在\n");
        return;
    }
    while (lead != NULL) //打印多项式
    {
        follow = lead;
        lead = lead->next;
        //打印规则

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
    if (lead == NULL) //检测多项式是否存在
    {
        printf("error:多项式不存在\n");
        return;
    }
    while (lead != NULL) //打印多项式
    {
        follow = lead;
        lead = lead->next;
        //打印规则

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
        printf("error:多项式A不存在\n");
    if (B->next == NULL)
        printf("error:多项式B不存在\n");

    pol *AND, *pA, *pB, *p, *follow, *lead, *temp;
    AND = (pol *)malloc(sizeof(pol));
    AND->next = NULL;
    p = follow = AND;
    pA = A;
    while (pA != NULL) //复制A到AND
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
    while (pB != NULL) //插入B到AND
    {
        pol_record(AND, pB->coef, pB->index, 1);
        pB = pB->next;
    }
    follow = lead = AND;
    follow = lead;
    lead = lead->next;
    if (lead == NULL) //没有项即所有项消去时为0
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

    printf("--------------------请逐步输入多项式 A-------------------- \n\n");
    while (1)
    {
        printf("请输入系数&指数：");
        scanf("%lf%d", &coef, &index);
        pol_record(A, coef, index, 0);
        pol_print(A);
        printf("\n");
        printf("继续？(回车继续，输入n退出):");
        getchar();
        scanf("%c", &choice);
        if (choice == 'n')
            break;
    }
    printf("\n--------------------请逐步输入多项式 B-------------------- \n\n");
    while (1)
    {
        printf("请输入系数&指数：");
        scanf("%lf%d", &coef, &index);
        pol_record(B, coef, index, 0);
        pol_print(B);
        printf("\n");
        printf("继续？(回车继续，输入n退出):");
        getchar();
        scanf("%c", &choice);
        if (choice == 'n')
            break;
    }
    printf("\n--------------------请逐步输入多项式 C-------------------- \n\n");
    while (1)
    {
        printf("请输入系数&指数：");
        scanf("%lf%d", &coef, &index);
        pol_record(C, coef, index, 0);
        pol_print(C);
        printf("\n");
        printf("继续？(回车继续，输入n退出):");
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
