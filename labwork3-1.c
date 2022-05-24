/*
    输入一个中缀算术表达式，计算其结果。对输入的表达式，做如下假设：
    (1)只考虑+、-、*、/这四种运算符；
    (2)输入的中缀表达式中数字只有整数，没有小数；
    (3)假定输入表达式是合法的。

    扩展问题：
    如果表达式加入括号和乘方运算，算法和程序如何改变？
*/

#include <string.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>

//定义优先级
int priority(char opt)
{
    switch(opt)
    {
    case'+':
        return 2;
    case'-':
        return 2;
    case'*':
        return 3;
    case'/':
        return 3;
    case'^':
        return 4;
    case'(':
        return 0;
    case')':
        return 1;
    default:
        return 0;
    }
}

//万能运算函数
double calculate(double a,double b,char sign)
{
    switch(sign)
    {
    case '+':
        return b+a;
    case '-':
        return b-a;
    case '*':
        return b*a;
    case '/':
        return b/a;
    case '^':
        return pow(b,a);
    default:
        return 0;
    }
}

int main()
{
    FILE * p = fopen("labwork3-1-read.txt","r");
    FILE * out = fopen("labwork3-1-out.txt","w");
    char s[100];
    char opt[50] = {0};
    double temp[50] = {0};
    int a = 0, b = 0;
    fscanf(p,"%[^EOF]",s);//读取文件中的多项式
    puts(s);

    int lenth = strlen(s);
    char * flag = s;
    int nums = 0;

    //读取字符
    for(int i = 0; i < lenth; i++)
    {
        if(* flag >= '0' && * flag <= '9')
        {
            //printf("检测到数字 %c:\t",* flag);
            while(* flag >= '0' && * flag <= '9')//如果检测到数字
            {
                nums = nums * 10 + (* flag - '0');
                flag ++, i ++;
            }
            temp[a] = nums;
            printf("计入temp[%d] = %.2f\n",a,temp[a]);


            nums = 0, a ++, i --;//i多加了一次
        }
        else//如果检测到其他字符
        {
            printf("检测到字符 %c:\t",* flag);
            //检测负号
            if(* flag != ' ')
            {
                if((* flag == '-') && (a == 0 || *(flag -1) == '('))
                {
                    printf("检测为负号\n");
                    temp[a] = -1;
                    a ++;
                    opt[b] = '*';
                    b ++;
                }
                else
                {
                    if(b > 0 && a > 0)//如果优先级小于等于上一个，上一个进行运算
                    {
                        printf("p(flag) = %d,p(b-1) = %d\n\t", priority(* flag), priority(opt[b-1]));
                        while((priority(* flag) <= priority(opt[b-1])) && (* flag != '('))
                        {
                            a --;
                            printf("\n\t* flag = '%c'优先级小于或等于 opt[%d] = '%c'\n",* flag,b-1,opt[b-1]);
                            printf("\t计算结果temp[%d]= %.2f '%c' temp[%d]=%.2f", a-1, temp[a-1], opt[b-1], a, temp[a]);
                            temp[a-1] = calculate(temp[a],temp[a-1],opt[b-1]);
                            printf("=> temp[%d] = %.2f\n\t\t", a-1, temp[a-1]);
                            b --;
                        }
                    }
                    opt[b] = * flag;
                    printf("计入opt[%d] = %c\n\n", b, * flag);
                    if(opt[b] == ')')
                        b -= 2;
                    b ++;
                }
            }
            flag ++;
        }
    }

    if(opt[0] != 0) //读到文件尾部
    {
        a--, b--;
        printf("\n已读到文件尾部，最后运算\n");
        do
        {
            printf("\t计算结果temp[%d]= %.2f '%c' temp[%d]=%.2f", a-1, temp[a-1], opt[b], a, temp[a]);
            temp[a-1] = calculate(temp[a],temp[a-1],opt[b]);
            printf("=> temp[%d] = %.2f\n\n", a-1, temp[a-1]);
            opt[b] = 0, b --, a --;
        }
        while(opt[0] != 0);
    }
    printf("最终答案：%.2f\n",temp[0]);
    fprintf(out,"%.2f",temp[0]);
    return 0;
}
