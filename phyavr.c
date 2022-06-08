#include <stdio.h>
#include <math.h>

int main()
{
    FILE * p = fopen("phyavr-out.txt","a");
    double a1, a2, a3, a4, a5, average;
    printf("five value:\n");
    scanf("%lf %lf %lf %lf %lf",&a1,&a2,&a3,&a4,&a5);
    average = (a1 + a2 + a3 + a4 + a5)/5;
    printf("average = %f\n",average);

    double deltai, tpn = 1.14, ux, ua, ub, n = 5.;
    printf("deltai = ");
    scanf("%lf", &deltai);
    ua = tpn * sqrt((pow((a1-average),2) + pow((a2-average),2)
                     + pow((a3-average),2) + pow((a4-average),2)
                      + pow((a5-average),2))/(n * (n-1)));
    ub = deltai/sqrt(3.0);
    ux = sqrt(ua * ua + ub * ub);
    printf("ua = %e, ub = %e, ux = %e\n", ua, ub, ux);
    fprintf(p,"%e\t%e\t%e\t%e\t%e\n",
            average,ux,deltai,ua,ub);
    fclose(p);
    return 0;
}