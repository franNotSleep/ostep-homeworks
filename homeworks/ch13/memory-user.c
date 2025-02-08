#include <unistd.h>
#include <sys/time.h>
#include <stdlib.h>
#include <stdio.h>

time_t getseconds() {
  struct timeval tv;
  gettimeofday(&tv, NULL);
  return tv.tv_sec;
}

int main(int argc, char **argv)
{

  if (argc != 3) {
    printf("usage: %s <nmb> <sec>\n", argv[0]);
    exit(1);
  }

  int pid = getpid();

  printf("pid: %d\n", pid);

  int nmb = atoi(argv[1]) * 1048576;
  int *arr = (int *)malloc(sizeof(int) * nmb);

  int sec = atoi(argv[2]);
  struct timeval end;
  gettimeofday(&end, NULL);
  end.tv_sec = end.tv_sec + sec;

  while (getseconds() < end.tv_sec) {
    for (int i = 0; i < nmb; i++) {
      arr[i] = 0;
    }
  }

  free(arr);
}
