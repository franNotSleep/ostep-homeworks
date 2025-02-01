#include <stdio.h>
#include <unistd.h>
#include <sys/time.h>
#include <fcntl.h>
#include <assert.h>
#include <sys/types.h>

#define SYSCALL_N 10

int
main(int argc, char **argv)
{
  int fd = open("./measure_syscall", O_CREAT, S_IRUSR);
  assert(fd != -1);

  struct timeval start = { 0, 0 };
  if (gettimeofday(&start, NULL) == -1) {
      perror("start: ");
  }

  long long start_mill = start.tv_usec * 0.001;

  for (int i = 0; i < SYSCALL_N; i++) {
    getpid();
 //   if (read(fd, NULL, 0) == -1) {
 //     perror("read: ");
 //   }
  }

  struct timeval end = { 0, 0 };
  if (gettimeofday(&end, NULL) == -1) {
      perror("end: ");
  }

  long long end_mill = end.tv_usec * 0.001;

  printf("total duration: %8lu (sec) %8llu (mill) %8lu (micr)\n", end.tv_sec - start.tv_sec, end_mill - start_mill ,end.tv_usec - start.tv_usec);
//  printf("syscall duration: %8lu (sec) %8llu (mill) %8lu (micr)\n", end.tv_sec - start.tv_sec, end_mill - start_mill ,end.tv_usec - start.tv_usec);
}
