#include<stdio.h>
#include<math.h>
#include<string.h>
#include<algorithm>
using namespace std;
typedef unsigned long long ull;
char a[1000010];
char s[1000010];
ull ha[1000010];
int main()
{
    ull hs=0,pow1=1;
    scanf("%s",a);
    scanf("%s",s);
    int b=123,i;//b值是任意定义，素数即可
    int la=strlen(a);
    int ls=strlen(s);
    for(i=0;i<ls;i++)//计算模式串的哈希值
    {
        hs=hs*b+(ull)(s[i]);
        pow1*=b;
    }
    ha[0]=a[0];
    for(i=1;i<la;i++)
        ha[i]=ha[i-1]*b+(ull)(a[i]);//计算主串每一段的哈希值
    int k=0;
    printf("pow1 = %d\n",pow1);
    for(i=ls-1;i<la;i++)
    {
        printf("ha[%d] = %d, ha[%d] = %d\n",i,ha[i],i-ls,ha[i-ls]);
        if(i-ls<0&&ha[i]==hs)//长度和模式串相等
            k++;
        else if(ha[i]-ha[i-ls]*pow1==hs)
            k++;
    }
    printf("%d\n",k);
    return 0;
}
// ————————————————
// 版权声明：本文为CSDN博主「Piink」的原创文章，遵循CC 4.0 BY-SA版权协议，转载请附上原文出处链接及本声明。
// 原文链接：https://blog.csdn.net/Piink/article/details/109536916