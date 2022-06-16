#include <stdio.h>
#include <math.h>

int main()
{
    FILE * fp = fopen("phy2-5-out.txt", "a");
    double nita, p, p0, d, g, h, v, D, L, t;
    p = 11.305e3;
    p0 = 0.965e3;
    g = 9.793;
    h = 31.772e-2;
    L = 22.598e-2;
    D = 63.7e-3;
    scanf("%lf %lf", &d, &t);
    d = d/1000;
    v = L/t;
    printf("v = %f\n", v);
    nita = ((p - p0) * (d * d) * g * t)/( 18 * L * (1. + 2.4 * (d/D)) * (1. + 3.3 * (d/(2 * h)) ));
    printf("nita = %e\n", nita);
    fprintf(fp, "%e\n", nita);
    return 0;
    fclose(fp);
}