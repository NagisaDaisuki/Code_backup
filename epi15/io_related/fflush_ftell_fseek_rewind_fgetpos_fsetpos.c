#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define FILENAME "demo_file.txt"

int main(void) {
  FILE *fp;

  // ===================================================================
  // 1. 打开文件并写入数据 (使用 "w+" 模式允许读写)
  // ===================================================================

  fp = fopen(FILENAME, "w+");
  if (fp == NULL) {
    perror("Error opening file");
    return EXIT_FAILURE;
  }

  printf("--- 开始写入和控制文件指针 ---\n");

  // 写入第一个字符串
  fputs("ABCDEFGHIJKLMNOP", fp);
  printf("1. 写入 'ABCDEFGHIJKLMNOP'\n");

  // -- fflush 示例 --
  // 尽管没有换行符，fflush 也会强制将数据从缓冲区写入磁盘
  fflush(fp); // fputs没有写入换行符，这里本来fputs的
              // 第一个参数写入到缓冲区还未到fp中，但是
              // 执行fflush可以强制从缓冲区写入磁盘
  printf("2. 使用fflush 强制刷新数据到文件。\n");

  // -- ftell 和 fgetpos 示例 --

  long initial_pos = ftell(fp); // 记录当前位置 （通常是16，即字符串末尾）
  fpos_t saved_fpos;
  fgetpos(fp, &saved_fpos); // 记录当前位置到 fpos_t 结构体中

  printf("3. 当前文件指针位置(ftell): %ld\n", initial_pos);

  // 写入第二个字符串
  fputs("XYZ", fp);
  printf("4. 写入 'XYZ'。\n");

  // -- fssek 示例 --
  // fseek(stream, offset, origin);
  // origin: SEEK_SET 从文件开头， SEEK_CUR 从当前位置，SEEK_END 从文件末尾

  // 将指针 重新定位到第五个字符(索引5)
  fseek(fp, 5, SEEK_SET);
  printf("5. 使用 fseek(5, SEEK_SET) 跳转到索引5。\n");

  // 写入新数据 ，会覆盖掉原有的 'FGHI'
  fputs("1234", fp);
  printf("6. 写入 '1234' (覆盖掉原有的 'FGHI').\n");

  // -- fsetpos 示例 --

  // 将指针重新定位回之前 fgetpos 记录的位置 (initial_pos = 16)
  fsetpos(fp, &saved_fpos);
  printf("7. 使用 fsetpos 跳转回保存的位置(%ld)。\n", initial_pos);

  // 写入数据，会在 16 处 继续 写入
  fputs("999", fp);
  printf("8. 写入'999'。\n");

  // --- rewind 示例 ---
  rewind(fp);
  printf("9. 使用 rewind 将指针 重置到文件开头。\n");

  // ===================================================================
  // 2. 从开头读取最终文件内容
  // ===================================================================

  printf("\n--- 读取文件内容进行验证 ---\n");
  char buffer[50];

  // 尝试从头读取整个文件
  if (fgets(buffer, sizeof(buffer), fp) != NULL)
    printf("文件最终内容：%s\n", buffer);
  else
    printf("读取文件失败\n");

  fclose(fp);

  return EXIT_SUCCESS;
}
