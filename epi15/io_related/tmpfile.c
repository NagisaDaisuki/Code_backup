#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(void) {
  FILE *tmp_fp;
  char write_data[] = "Temporary data buffer";
  char read_buffer[100];

  // 1. 创建临时文件流
  // FILE* tmpfile(void);
  tmp_fp = tmpfile();

  if (tmp_fp == NULL) {
    perror("Failed to open tmpfile.\n");
    return EXIT_FAILURE;
  }

  printf("成功创建临时文件流。该文件将在程序退出时自动删除。\n");

  // 2. 写入数据到临时文件
  if (fputs(write_data, tmp_fp) != EOF) {
    printf("写入数据成功：\"%s\"\n", write_data);
  } else {
    perror("Error writing to temporary file");
  }

  // 3. 将文件指针重置到开头
  rewind(tmp_fp);

  // 4. 从临时文件读取数据
  if (fgets(read_buffer, sizeof(read_buffer), tmp_fp) != NULL) {
    printf("从临时文件读取数据：\"%s\"\n", read_buffer);
  } else {
    perror("Error reading from temporary file");
  }

  // 5. 关闭文件流
  // 当文件流关闭时，操作系统会自动删除这个临时文件

  if (fclose(tmp_fp) == 0) {
    printf("\n临时文件流关闭成功，临时文件已被删除。\n");
  } else {
    perror("Error closing temporary file");
  }

  return EXIT_SUCCESS;
}
