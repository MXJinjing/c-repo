#include <stdio.h>
#include <math.h>

int main()
{
    FILE * p = fopen("phy2-5-out.txt", "a");
    double nita, p, p0, d, g, v, D, L, t;
    p = 11305;
    p0 = 0.965;
    g = 9.793;

    nita = ((1/18) * (p - p0) * (d * d) * g * t)/
            L * (1. + 2.4 * (d/D)) * (1. + 3.3 * (d/(2 * h)) );
    printf("nita = %e\n", nita);
    return 0;
}