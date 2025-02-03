#define _GNU_SOURCE
#include <sched.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/time.h>
#include <sys/types.h>

#define MAX_ITER 10

int
main(int argc, char **argv) 
{
  struct timeval start, end;
  cpu_set_t set;

  int fd1[2];
  int fd2[2];
  pid_t pid;
  if (pipe(fd1) == -1) {
    perror("pipe1: ");
  }

  if (pipe(fd2) == -1) {
    perror("pipe2: ");
  }

  if ((pid = fork()) == -1) {
    perror("fork: ");
  }

  if (pid > 0) {
    CPU_SET(1, &set);
    sched_setaffinity(pid, sizeof(cpu_set_t), &set);
    for (int i = 0; i < MAX_ITER; i++) {
      write(fd1[1], NULL, 0);
      read(fd2[0], NULL, 0);
    }
  } else {
    CPU_SET(1, &set);
    sched_setaffinity(getpid(), sizeof(cpu_set_t), &set);
    gettimeofday(&start, NULL);
    for (int i = 0; i < MAX_ITER; i++) {
      read(fd1[0], NULL, 0);
      write(fd2[1], NULL, 0);
    }
    gettimeofday(&end, NULL);

    printf("ctx switch in microseconds: %f\n", ((1000000 * end.tv_sec + end.tv_usec) - (1000000 * start.tv_sec + start.tv_usec)) / (float)MAX_ITER);
  }
}
