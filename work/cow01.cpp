// 给定一个长度为 n 的非负整数序列 A ，求一个平均数最大的，长度不小于 L 的子段。
// 输入格式:
// 第一行用空格分隔的两个整数 n 和 L；
// 第二行为 n 个用空格隔开的非负整数，表示 A_i。
// 1≤n≤10^5
// 0≤A_i≤2000
// 输出格式:
// 输出一个整数，表示这个平均数的 1000 倍。不用四舍五入，直接输出。

#include <future>
#include <iostream>
#include <istream>
#include <stdio.h>
#define MAXN 100010
using namespace std;

long n, l, a[MAXN];
int main() {
  cin >> n >> l;
  for (long i = 0; i < n; i++) {
    cin >> a[i];
    
  }
  return 0;
}