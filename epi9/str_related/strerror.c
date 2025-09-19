#include <errno.h>
#include <stdio.h>
#include <string.h>

// 必须包含此头文件来使用 errno

int main(void) {
  FILE *file;
  // 尝试打开一个不存在的文件
  file = fopen("non_existent_file.txt", "r");

  // 如果 fopen 失败
  if (file == NULL)
    printf("Error opening file: %s\n", strerror(errno));
  else {
    printf("File opened successfully.\n");
    fclose(file);
  }
  return 0;
}
