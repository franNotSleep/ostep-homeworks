#include <stdlib.h>
#include <stdio.h>

int main(int argc, char **argv)
{
  int *data = (int *)malloc(sizeof(int) * 100);

  for (int i = 0; i < 100; i++) {
    data[i] = 0;
  }

  free(data);
  free(1);

  printf("data[0] = %d\n", data[0]);
}
