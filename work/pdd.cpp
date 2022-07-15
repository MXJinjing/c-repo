#include <algorithm>
#include <bits/stdc++.h>
#include <cstdio>
#include <type_traits>
#define MAXN 10010
using namespace std;
typedef pair<double, double> pt;

int n;
double a , b, r , disa, disb, xo, yo, qo;
pt s[MAXN], stk1[MAXN], stk2[MAXN], temp;

//基本运算
pt rotate(pt a, double q)
{
    return { a.first * cos(q) + a.second * cos(q), -a.first * sin(q) + a.second * cos(q) };
}
pt operator-(pt a, pt b)
{
    return { a.first - b.first, a.second - b.second };
}
double cross(pt a, pt b)
{
    return a.first * b.second - a.second * b.first;
}
double area(pt a, pt b, pt c)
{
    return cross(b - a, c - a);
}
double dist2(pt a, pt b)
{
    double _x = a.first -b.first;
    double _y = a.second - b.second;
    return _x * _x + _y * _y;
}
double dist(pt a, pt b)
{
    return sqrt(dist2(a, b));
}

int main()
{
    scanf("%d %lf %lf %lf", &n, &a, &b, &r);
    disa = a/2. - r, disb = b/2. - r;
    for (int i = 0; i <n; i++){
        scanf("%lf%lf%lf",&xo, &yo, &qo);
        temp = {b,a}
    }
    return 0;
}