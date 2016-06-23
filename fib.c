
#include <stdlib.h>
#include <stdio.h>
#include <getopt.h>
#include <unistd.h>
#include <time.h>

typedef unsigned long long long_t;

long_t fibRecursion(int n)
{
  long_t result;
  if (n == 0)
    result = 0;
  else if (n == 1)
    result = 1;
  else
    result = fibRecursion(n - 1) + fibRecursion(n - 2);
  
  return result;
}

long_t fibDynamic(int n)
{
  long_t *arr = malloc(sizeof(long_t) * (n + 1));
  arr[0] = 0;
  arr[1] = 1;
  int i;
  for (i = 2; i < n + 1; i++) {
    arr[i] = arr[i - 1] + arr[i - 2];
  }
  long_t result = arr[n];
  free(arr);
  return result;
}

int main (int argc, char **argv) 
{
  if (argc <  2) 
    {
      fprintf(stderr, "Incorrect usage: must supply number as argument.");
      exit(1);
    }
  
  int num = atoi(argv[1]);
  //printf("Number supplied was: %d.\n", num);
  if(num > 93) {
    printf("n is too large. Must be less than 94.\n");
    return 1;
  }

  int dflag = 0; //enables dynamic programming instead of recursion
  int tflag = 0; //enables timing
  
  //options
  char c;
  while((c = getopt(argc, argv, "dt")) != -1) {
      switch (c) {
	case 'd':
	  dflag = 1;
	  break;
	case 't':
	  tflag = 1;
	  break;
      }
  }
  //printf("D: %d, T: %d\n", dflag, tflag);

  double accum;
  struct timespec start, stop;
  if (tflag == 1) {
    if( clock_gettime( CLOCK_MONOTONIC, &start) == -1 ) {
      perror( "clock gettime" );
      exit(1);
    }
  }

    
  long_t result;
  if (dflag == 1)
    result = fibDynamic(num);
  else
    result = fibRecursion(num);
  if (tflag == 1) {
    if( clock_gettime( CLOCK_MONOTONIC, &stop) == -1 ) {
      perror( "clock gettime" );
      exit(1);
    }

    accum = ( stop.tv_sec - start.tv_sec )
      + (( stop.tv_nsec - start.tv_nsec )
	 / 1000000000.0);
  }
  
  printf("Result is %llu\n", result);
  if (tflag == 1)
    printf( "The operation took %lf seconds.\n", accum );
  return 0;
	
}
