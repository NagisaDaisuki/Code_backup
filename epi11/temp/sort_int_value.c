/*
 *  读取、排序和打印一列整型值
 *
 * */
#include <stdio.h>
#include <stdlib.h>

/*
 *  该函数由 `qsort` 调用，用于比较整型值。
 * */
int compare_integers(void const *a, void const *b) {
  register int const *pa = a;
  register int const *pb = b;

  return *pa > *pb ? 1 : *pa < *pb ? -1 : 0;
}

int main(void) {
  int *array;
  int n_values;
  int i;

  // 观察共有多少个值

  printf("How many values are there? ");
  if (scanf("%d", &n_values) != 1 || n_values <= 0) {
    printf("Illegal number of values.\n");
    exit(EXIT_FAILURE);
  }

  // 分配内存，用于存储这些值。
  array = malloc(n_values * sizeof(int));
  if (array == NULL) {
    printf("Can't get memory for that many values.\n");
    exit(EXIT_FAILURE);
  }

  // 读取这些数值
  for (i = 0; i < n_values; i += 1) {
    printf("? ");
    if (scanf("%d", array + i) != 1) {
      printf("Error reading value #%d\n", i);
      free(array);
      exit(EXIT_FAILURE);
    }
  }

  // 对这些值排序
  qsort(array, n_values, sizeof(int), compare_integers);

  // 打印这些值
  for (i = 0; i < n_values; i += 1) {
    printf("%d\n", array[i]);
  }

  // 释放内存并退出
  free(array);
  return EXIT_SUCCESS;
}

/*
 *  排列一列整型值
 * */
