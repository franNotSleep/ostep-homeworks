#include <assert.h>
#include <stdio.h>
#include <stddef.h>
#include <stdlib.h>

struct Vector {
  size_t len;
  size_t cap;
  void **data;
};

struct Vector *init(size_t init_cap) {
  struct Vector *arr = (struct Vector*)malloc(sizeof(struct Vector));
  arr->len = 0;
  assert(arr != NULL);

  arr->cap = init_cap;
  arr->data = (void **)malloc(sizeof(void *) * init_cap);
  return arr;
}

void clear(struct Vector *arr) {
  free(arr->data);
  free(arr);
}

void increase(struct Vector *arr) {
  size_t new_cap = (arr->cap + 1) * 2;
  void **ptr = (void **)realloc(arr->data, new_cap * sizeof(void *));

  if (ptr == NULL) {
    perror("realloc: ");
    exit(1);
  }
  arr->data = ptr;
  arr->cap = new_cap;
}

void *pop(struct Vector *arr) {
  size_t indx = arr->len - 1;
  arr->len--;
  void *v = arr->data[indx];
  arr->data[indx] = 0;
  return v;
}


void push(struct Vector *arr, void *new_value) {
  if (arr->cap == arr->len) {
    increase(arr);   
  }

  arr->data[arr->len] = new_value;
  arr->len++;
}

int
main(int argc, char **argv) 
{

  struct Vector *arr = init(3);

  int v1 = 1;
  char v2 = 'c';
  char *v3 = "some_name";

  push(arr, &v1);
  push(arr, &v2);
  push(arr, &v3);

  printf("len: %4lu \ncap: %4lu\n", arr->len, arr->cap);
  printf("v1: %5d\n", *(int *)arr->data[0]);
  printf("v2: %5c\n", *(char *)arr->data[1]);
  printf("v3: %*s\n", 10, *(char **)arr->data[2]);
  printf("len: %4lu \ncap: %4lu\n", arr->len, arr->cap);

  push(arr, &v1);
  push(arr, &v2);
  push(arr, &v3);
  push(arr, &v1);
  push(arr, &v1);
  push(arr, &v2);
  push(arr, &v3);

  printf("len: %4lu \ncap: %4lu\n", arr->len, arr->cap);
  pop(arr);
  char c = *((char *)pop(arr));
  printf("char: %c\n", c);
  pop(arr);
  pop(arr);
  pop(arr);
  pop(arr);

  printf("len: %4lu \ncap: %4lu\n", arr->len, arr->cap);
  clear(arr);
}
