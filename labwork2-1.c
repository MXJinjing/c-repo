/*
    设有两个一元多项式A(x),B(x)，请完成运算A(x)+B(x)、A(x)-B(x)，要求多项式采用链表结构进行存储，
    多项式可以按照升幂（降幂）形式输入对应的系数、指数项，但对输入输出格式不做要求。
    
    扩展问题：
    (1)一元多项式的乘法运算，如何实现？
    (2)一元多项式的除法运算，如何实现？
    (3)多元多项式的加法，如何实现？
*/

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

typedef struct polynomial
{
    double coef;   //系数
    int index;  //指数
    struct polynomial * next;
} pol;

typedef struct pol_with_leave
{
    pol * main;
    pol * leave_num;
    pol * leave_den;
} pol3;

void pol_record(pol * head, double coef, int index, int mod) //按降幂记录多项式
{
    pol * lead, * follow, *p;
    p = (pol *)malloc(sizeof(pol));
    p->next = NULL;
    p->coef = coef;
    p->index = index;

    if(p->index < 0)    //检查指数范围
    {
        printf("error:指数不能为负\n");
        return;
    }

    lead = follow = head;
    while(1)
    {
        follow = lead;
        lead = lead->next;
        if(lead == NULL) //在尾部插入新项
        {
            follow->next = p;
            break;
        }
        if(lead->index == p->index)//当匹配到相同指数
        {
            if(mod == 1)//加法模式
                p->coef += lead->coef;
            lead->coef = p->coef;
            break;
        }
        if((lead->index < p->index && follow->index > p->index)
                ||(lead->index < p->index && follow == head))//在头或者中间插入
        {
            follow->next = p;
            p->next = lead;
            break;
        }
    }
    follow = head;
    lead = follow->next;
    while(lead != NULL)   //自动删除多余0
    {
        if( lead->coef == 0)//当匹配到系数为0
            follow->next=lead->next;
        follow = lead;
        lead = lead->next;
    }
    lead = head->next;
    if(lead == NULL)  //没有项即所有项消去时为0
    {
        pol * temp;
        temp = (pol *)malloc(sizeof(pol));
        temp->next = NULL;
        temp->coef = 0;
        temp->index = 0;
        head->next = temp;
    }
    return;
}

void pol_print(pol * head)
{
    FILE * p = fopen("labwork2-1-out.txt","a");
    pol * lead, * follow;
    lead = follow = head->next;
    if(lead == NULL)   //检测多项式是否存在
    {
        printf("error:多项式不存在\n");
        return;
    }
    while(lead != NULL) //打印多项式
    {
        follow = lead;
        lead = lead->next;
        //打印规则

        if(!(follow->index == 0 || follow->index == 1 || follow->index == -1))
            if(follow->coef ==1)
                {
                    printf("x^%d",follow->index);
                }
            else
                {
                    printf("%.2gx^%d",follow->coef,follow->index);
                }
        else
        {
            if(follow->index == 0)
                {
                    printf("%.2g",follow->coef);
                }
            if(follow->index == 1)
                if(follow->coef == 1)
                {
                    printf("x");
                }

                else
                {
                    if(follow->coef == -1)
                    {
                        printf("-x");
                    }

                    else {
                        printf("%.2gx",follow->coef);
                    }
                }
        }
        if(lead != NULL)
        {
            if(lead->coef >= 0)
            {
                printf("+");
            }

        }
    }
}

void pol_print_file(pol * head)
{
    FILE * p = fopen("labwork2-1-out.txt","a");
    pol * lead, * follow;
    lead = follow = head->next;
    if(lead == NULL)   //检测多项式是否存在
    {
        printf("error:多项式不存在\n");
        return;
    }
    while(lead != NULL) //打印多项式
    {
        follow = lead;
        lead = lead->next;
        //打印规则

        if(!(follow->index == 0 || follow->index == 1 || follow->index == -1))
            if(follow->coef ==1)
                {
                    fprintf(p,"x^%d",follow->index);
                    printf("x^%d",follow->index);
                }
            else
                {
                    fprintf(p,"%.2gx^%d",follow->coef,follow->index);
                    printf("%.2gx^%d",follow->coef,follow->index);
                }
        else
        {
            if(follow->index == 0)
                {
                    fprintf(p,"%.2g",follow->coef);
                    printf("%.2g",follow->coef);
                }
            if(follow->index == 1)
                if(follow->coef == 1)
                {
                    fprintf(p,"x");
                    printf("x");
                }

                else
                {
                    if(follow->coef == -1)
                    {
                        fprintf(p,"-x");
                        printf("-x");
                    }

                    else {
                        fprintf(p,"%.2gx",follow->coef);
                        printf("%.2gx",follow->coef);
                    }
                }
        }
        if(lead != NULL)
        {
            if(lead->coef >= 0)
            {
                fprintf(p,"+");
                printf("+");
            }

        }
    }
    fprintf(p,"\n");
    fclose(p);
}

pol * cal_and(pol * A, pol * B)
{
    if(A->next == NULL)
        printf("error:多项式A不存在\n");
    if(B->next == NULL)
        printf("error:多项式B不存在\n");

    pol * AND, * pA, * pB, * p, * follow, * lead, * temp;
    AND = (pol *)malloc(sizeof(pol));
    AND ->next = NULL;
    p = follow = AND;
    pA = A;
    while(pA!= NULL)    //复制A到AND
    {
        if(p == NULL)
        {
            p = (pol *)malloc(sizeof(pol));
            p->coef = pA->coef;
            p->index = pA->index;
            p->next = NULL;
            follow ->next = p;
        }
        follow = p;
        p = p->next;
        pA = pA->next;
    }
    pB = B->next;
    while(pB!= NULL)    //插入B到AND
    {
        pol_record(AND,pB->coef,pB->index,1);
        pB = pB->next;
    }
    follow = lead = AND;
    follow = lead;
    lead = lead->next;
    if(lead == NULL)  //没有项即所有项消去时为0
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

pol * cal_sub(pol * A,pol * B)
{
    if(A->next == NULL)
        printf("error:多项式A不存在\n");
    if(B->next == NULL)
        printf("error:多项式B不存在\n");
    pol * pB,* B_, *p,* follow,* sub;
    pB = B;

    //先将B的系数取相反数
    B_ = (pol *)malloc(sizeof(pol));
    B_->next = NULL;
    p = follow = B_;
    while(pB!= NULL)    //计算-B
    {
        if(p == NULL)
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
    sub = cal_and(A,B_);
    return sub;
}

pol * cal_mul(pol * A, pol * B)
{
    pol * MUL, * follow, * lead, *pA, *pB;
    int tempi;
    double tempc;
    pA = A->next;
    pB = B->next;
    MUL = (pol *)malloc(sizeof(pol));
    MUL->next = NULL;
    while (pA != NULL)
    {
        pB = B->next;
        while(pB != NULL)
        {
            tempc = pA->coef * pB->coef; //系数相乘
            tempi = pA->index + pB->index;  //指数相加
            pol_record(MUL,tempc,tempi,1);
            pB = pB->next;
        }
        pA = pA->next;
    }
    return MUL;
}

pol3 * cal_div(pol * A, pol * B)
{
    pol *A_, * pA, * pB, * DIV, * p, * temp, * follow, * lead, * temp2, * B_,*ptemp;
    pol3 * ANSWER;
    ANSWER = (pol3 *)malloc(sizeof(pol3));
    DIV  = (pol *)malloc(sizeof(pol));
    DIV->next = NULL;
    A_ = (pol *)malloc(sizeof(pol));
    A_->next = NULL;
    p = follow = A_;
    pA = A;
    while(pA!= NULL)    //复制A到A_
    {
        if(p == NULL)
        {
            p = (pol *)malloc(sizeof(pol));
            p->coef = pA->coef;
            p->index = pA->index;
            p->next = NULL;
            follow ->next = p;
        }
        follow = p;
        p = p->next;
        pA = pA->next;
    }

    B_ = (pol *)malloc(sizeof(pol));
    B_->next = NULL;
    p = follow = B_;
    pB = B;
    while(pB!= NULL)    //复制B到B_
    {
        if(p == NULL)
        {
            p = (pol *)malloc(sizeof(pol));
            p->coef = pB->coef;
            p->index = pB->index;
            p->next = NULL;
            follow ->next = p;
        }
        follow = p;
        p = p->next;
        pB = pB->next;
    }

    int tempi,tempi2,Aimin,Bimin,imin;
    double tempc, tempc2;
    pB = B_->next;
    pA = A_->next;
    int Bimax = pB->index;//B的最高次数
    double Bcmax = pB->coef;//B的最高次数项系数
    if(pA->index < Bimax)//如果没有A的次数小于B
    {
        ANSWER->main  = (pol *)malloc(sizeof(pol));
        ANSWER->main->next = NULL;
        pol_record(ANSWER->main,0,0,0);
        goto mark;
    }
    while((A_->next != NULL && pA->index >= Bimax))//如果A的次数大于B
    {
        //记录部分商
        tempc = pA->coef / Bcmax;
        tempi = pA->index - Bimax;
        pol_record(DIV,tempc,tempi,1);

        //记录单项商temp
        temp = (pol *)malloc(sizeof(pol));
        temp->next = NULL;

        lead = (pol *)malloc(sizeof(pol));;
        lead->coef = tempc;
        lead->index = tempi;
        lead->next = NULL;
        temp->next = lead;

        //A_减去算出的temp2
        ptemp = temp->next;
        pB = B_->next;
        lead = follow = temp;
        lead = lead->next;
        temp2 = cal_mul(B_,temp);

        A_ =cal_sub(A_,temp2);
        pA = A_->next;
    }
    ANSWER->main = DIV;
    pA = A_->next;
mark:
    //算出最小的次数
    for(lead = A_; lead != NULL; lead = lead->next)
        Aimin = lead->index;
    for(lead = B_; lead != NULL; lead = lead->next)
        Bimin = lead->index;
    if(Aimin > Bimin)
        imin = Bimin;
    else
        imin = Aimin;
    //约去多余的x
    if(imin != 0)
    {
        for(lead = A_->next; lead != NULL; lead = lead->next)
            lead->index -= imin;
        for(lead = B_->next; lead != NULL; lead = lead->next)
            lead->index -= imin;
    }
    if(A_->next->coef == 0 && A_->next->index == 0)
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
    pol * A, * B, * AND, *SUB, * MUL, * leave;
    pol3 * ANSWER;
    char choice;
    int index;
    double coef;
    choice = 'n';
    A = (pol *)malloc(sizeof(pol));
    A->next = NULL;
    B = (pol *)malloc(sizeof(pol));
    B->next = NULL;

    printf("--------------------请逐步输入多项式 A-------------------- \n\n");
    while(1)
    {
        printf("请输入系数&指数：");
        scanf("%lf%d",&coef,&index);
        pol_record(A,coef,index,0);
        pol_print(A);
        printf("\n");
        printf("继续？(回车继续，输入n退出):");
        getchar();
        scanf("%c",&choice);
        if(choice == 'n')
            break;
    }
    printf("\n--------------------请逐步输入多项式 B-------------------- \n\n");
    while(1)
    {
        printf("请输入系数&指数：");
        scanf("%lf%d",&coef,&index);
        pol_record(B,coef,index,0);
        pol_print(B);
        printf("\n");
        printf("继续？(回车继续，输入n退出):");
        getchar();
        scanf("%c",&choice);
        if(choice == 'n')
            break;
    }
    printf("\n");
    AND = cal_and(A,B);
    printf("\t");
    pol_print(A);
    printf("\n");
    printf("+");
    printf("\t");
    pol_print(B);
    printf("\n");
    printf("----------------------------------------------------------\n");
    printf("\t");
    pol_print_file(AND);
    printf("\n\n");

    SUB = cal_sub(A,B);
    printf("\t");
    pol_print(A);
    printf("\n");
    printf("-");
    printf("\t");
    pol_print(B);
    printf("\n");
    printf("----------------------------------------------------------\n");
    printf("\t");
    pol_print_file(SUB);
    printf("\n\n");

    MUL = cal_mul(A,B);
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
    printf("\n\n");

    ANSWER = cal_div(A,B);
    printf("\t");
    pol_print(A);
    printf("\n");
    printf("/");
    printf("\t");
    pol_print(B);
    printf("\n");
    printf("----------------------------------------------------------\n");
    printf("\t");
    if(!(ANSWER->main->next->index == 0 && ANSWER->main->next->coef == 0))
    {
        pol_print(ANSWER->main);
    }
    if(!(ANSWER->main->next->index == 0 && ANSWER->main->next->coef == 0) && (ANSWER->leave_den != NULL))
        printf("+");
    if(ANSWER->leave_den != NULL)
    {
        printf("(");
        pol_print(ANSWER->leave_num);
        printf(")/(");
        pol_print(ANSWER->leave_den);
        printf(")");
    }
    printf("\n\n");

    getchar();
    getchar();
    return 0;
}

