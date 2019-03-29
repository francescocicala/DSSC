#include<stdio.h>
#include<stdlib.h>
#include<omp.h>

double f(double x) {
  return 1 / (1 + x * x);
}



int main()
{
  long long int N = 100000000;
  double a = 0;
  double b = 1;
  double h = (b - a) / N;

  double sum = 0;

  for (int i = 0; i<N; ++i) {

    sum += h * f(a + i * h + 0.5 * h);

  }

  sum = 4 * sum;

  printf("Pi = %lf\n", sum);

  return 0;
}