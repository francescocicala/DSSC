#include<stdio.h>
#include<stdlib.h>
#include<omp.h>

double f(double x) {
  return 1 / (1 + x * x);
}



int main(int argc, char const *argv[])
{
  long long int N = 100000000;
  double a = 0;
  double b = 1;

  int nthreads = atoi(argv[1]);

  double h = (b - a) / N;

  double sum = 0.0;
  int i;

  double tstart = omp_get_wtime();
  #pragma omp parallel reduction(+:sum) num_threads(nthreads)
  { 
    #pragma omp for
    for (i = 0; i < N;  i++)
      sum += h * f(a + i * h);
  }

  sum = 4 * sum;
  double duration = omp_get_wtime() - tstart;
  printf("Pi = %lf\nDuration = %lf\n", sum, duration);

  return 0;
}