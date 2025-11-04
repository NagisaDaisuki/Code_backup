#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

int main(void) {
  char
      temp_filename[L_tmpnam]; // L_tmpnam 是 <stdio.h> 中的宏，保证缓冲区足够大
  FILE *fp;

  // 1. 生成一个唯一的文件名
  // 如果传入NULL， tmpnam 会使用 内部静态缓冲区，但我们使用局部数组更安全
  if (tmpnam(temp_filename) != NULL) {
    printf("生成的临时文件名是：%s\n", temp_filename);
  } else {
    fprintf(stderr, "tmpnam failed to generate temporary file.");
    return EXIT_FAILURE;
  }

  // 2. 手动创建和打开文件
  fp = fopen(temp_filename, "w");
  if (fp == NULL) {
    perror("Error opening the generated temporary file");
    return EXIT_FAILURE;
  }

  printf("手动创建并打开了文件。\n");

  // 3. 写入和关闭文件...
  fprintf(fp, "This is manually managed temporary data.\n");
  fclose(fp);

  // 4. 【重要】手动删除文件
  if (remove(temp_filename) == 0) {
    printf("手动删除了临时文件：%s\n", temp_filename);
  } else {
    perror("Error deleting temporary file");
  }
  return EXIT_SUCCESS;
}
