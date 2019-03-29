#include <stdlib.h>
#include <stdio.h>
#include <omp.h>

void print_usage( int * a, int N, int nthreads ) {

  int tid, i;
  for( tid = 0; tid < nthreads; ++tid ) {

    fprintf( stdout, "%d: ", tid );

    for( i = 0; i < N; ++i ) {

      if( a[ i ] == tid) fprintf( stdout, "*" );
      else fprintf( stdout, " ");
    }
    printf("\n");
  }
}

int main( int argc, char * argv[] ) {

  const int N = 250;
  int nthreads = atoi(argv[1]);
  int chunks_size;

  if (argc == 2) chunks_size = N / nthreads;
  else chunks_size = atoi(argv[2]);


  /************ STATIC *************/
  printf("\nSTATIC\n");
  int a[N];
  #pragma omp parallel num_threads( nthreads )
  {
  int thread_id = omp_get_thread_num();
  nthreads = omp_get_num_threads();
  
  int i;

  #pragma omp for schedule(static, chunks_size) //private(i)
  for(i=0; i < N; ++i)
    a[i] = thread_id;

  }

  printf("Static schedule: \n\tn_threads = %d\n\tchunks_size = %d\n", nthreads, chunks_size);
  print_usage(a, N, nthreads);


  /************ DYNAMIC *************/
  printf("\nDYNAMIC\n");
  int b[N];
  #pragma omp parallel num_threads( nthreads )
  {
  int thread_id = omp_get_thread_num();
  nthreads = omp_get_num_threads();
  
  int i;

  #pragma omp for schedule(dynamic, chunks_size) //private(i)
  for(i=0; i < N; ++i)
    b[i] = thread_id;

  }

  printf("Static schedule: \n\tn_threads = %d\n\tchunks_size = %d\n", nthreads, chunks_size);
  print_usage(b, N, nthreads);


  return 0;
}
