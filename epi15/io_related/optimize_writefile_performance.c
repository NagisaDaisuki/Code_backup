#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define FILENAME "big_buffer_test.txt"
#define CUSTOM_BUF_SIZE 4096 * 4 // 16 KB 的缓冲区大小

int main(void) {
  FILE *fp;
  char custom_buffer[CUSTOM_BUF_SIZE]; // 声明自定义的内存缓冲区

  // 1. 打开文件进行写入
  fp = fopen(FILENAME, "w");
  if (fp == NULL) {
    perror("Error opening file.");
    return EXIT_FAILURE;
  }

  // 2. 使用 setvbuf 设置为全缓冲模式， 并指定自定义缓冲区
  // 目标：只有当 16KB 缓冲区写满时，才进行一次磁盘写入操作
  int result = setvbuf(fp, custom_buffer, _IOFBF, CUSTOM_BUF_SIZE);

  if (result != 0) {
    fprintf(stderr, "setvbuf 设置失败!\n");
    fclose(fp);
    return EXIT_FAILURE;
  }

  printf("文件流已设置为 %zu 字节的全缓冲模式。\n", (size_t)CUSTOM_BUF_SIZE);

  // 3. 写入数据
  for (int i = 0; i < 100; i++) {
    fprintf(fp, "Line %d : This is buffered data.\n", i);
  }

  printf("数据已写入缓冲区，但可能尚未写入磁盘。\n");
  // 此时，数据仍在内存中的 custom_buffer 中，直到缓冲区满或关闭。

  // 4. 关闭文件(关闭时会自动冲刷缓冲区)
  fclose(fp);
  printf("文件已关闭，缓冲区内容已冲刷到磁盘。\n");

  // remove(FILENAME); // 清理原文件(可选)

  return EXIT_FAILURE;
}
