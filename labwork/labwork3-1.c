/*
    ����һ����׺�������ʽ������������������ı��ʽ�������¼��裺
    (1)ֻ����+��-��*��/�������������
    (2)�������׺���ʽ������ֻ��������û��С����
    (3)�ٶ�������ʽ�ǺϷ��ġ�

    ��չ���⣺
    ������ʽ�������źͳ˷����㣬�㷨�ͳ�����θı䣿
*/

#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//�������ȼ�
int priority(char opt)
{
    switch (opt)
    {
    case '+':
        return 2;
    case '-':
        return 2;
    case '*':
        return 3;
    case '/':
        return 3;
    case '^':
        return 4;
    case '(':
        return 9;
    case ')':
        return 1;
    default:
        return 0;
    }
}

//�������㺯��
double calculate(double a, double b, char sign)
{
    switch (sign)
    {
    case '+':
        return b + a;
    case '-':
        return b - a;
    case '*':
        return b * a;
    case '/':
        return b / a;
    case '^':
        return pow(b, a);
    default:
        return 0;
    }
}

int main()
{
    FILE *p = fopen("labwork3-1-read.txt", "r");
    FILE *out = fopen("labwork3-1-out.txt", "w");
    char s[100];
    char opt[50] = {0};
    double temp[50] = {0};
    int a = 0, b = 0;
    fscanf(p, "%[^EOF]", s); //��ȡ�ļ��еĶ���ʽ
    puts(s);

    int lenth = strlen(s);
    char *flag = s;
    int nums = 0;

    //��ȡ�ַ�
    for (int i = 0; i < lenth; i++)
    {
        if (*flag >= '0' && *flag <= '9')
        {
            // printf("��⵽���� %c:\t",* flag);
            while (*flag >= '0' && *flag <= '9') //�����⵽����
            {
                nums = nums * 10 + (*flag - '0');
                flag++, i++;
            }
            temp[a] = nums;
            printf("����temp[%d] = %.2f\n", a, temp[a]);

            nums = 0, a++, i--; // i�����һ��
        }
        else //�����⵽�����ַ�
        {
            printf("��⵽�ַ� %c:\t", *flag);
            //��⸺��
            if (*flag != ' ')
            {
                if ((*flag == '-') && (a == 0 || *(flag - 1) == '('))
                {
                    printf("���Ϊ����\n");
                    temp[a] = -1;
                    a++;
                    opt[b] = '*';
                    b++;
                }
                else
                {
                    if (b > 0 && a > 0)
                    {
                        printf("p(flag) = %d,p(b-1) = %d\n\t", priority(*flag), priority(opt[b - 1]));
                        while ((priority(*flag) <= priority(opt[b - 1])) && (opt[b - 1] != '('))
                        { //������ȼ�С�ڵ�����һ������һ����������
                            a--;
                            printf("\n\t* flag = '%c'���ȼ�С�ڻ���� opt[%d] = '%c'\n", *flag, b - 1, opt[b - 1]);
                            printf("\t������temp[%d]= %.2f '%c' temp[%d]=%.2f", a - 1, temp[a - 1], opt[b - 1], a, temp[a]);
                            temp[a - 1] = calculate(temp[a], temp[a - 1], opt[b - 1]);
                            printf("=> temp[%d] = %.2f\n\t\t", a - 1, temp[a - 1]);
                            b--;
                        }
                    }
                    opt[b] = *flag;
                    printf("����opt[%d] = %c\n\n", b, *flag);
                    if (opt[b] == ')')
                        b -= 2;
                    b++;
                }
            }
            flag++;
        }
    }

    if (opt[0] != 0) //�����ļ�β��
    {
        a--, b--;
        printf("\n�Ѷ����ļ�β�����������\n");
        do
        {
            printf("\t������temp[%d]= %.2f '%c' temp[%d]=%.2f", a - 1, temp[a - 1], opt[b], a, temp[a]);
            temp[a - 1] = calculate(temp[a], temp[a - 1], opt[b]);
            printf("=> temp[%d] = %.2f\n\n", a - 1, temp[a - 1]);
            opt[b] = 0, b--, a--;
        } while (opt[0] != 0);
    }
    printf("���մ𰸣�%.2f\n", temp[0]);
    fprintf(out, "%.2f", temp[0]);
    return 0;
}
