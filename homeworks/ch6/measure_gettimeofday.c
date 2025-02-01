#include <stdio.h>
#include <sys/time.h>
#include <stdlib.h>

int
main(int argc, char **argv)
{
  struct timeval *tv = malloc(sizeof(struct timeval));
  if (gettimeofday(tv, NULL) == -1) {
    perror("gettimeofday: ");
  }

  printf("seconds: %lu\n", tv->tv_sec);
  printf("milliseconds: %lf\n", tv->tv_sec * 0.001);
  printf("microseconds: %lu\n", tv->tv_usec);

  return 0;
}
