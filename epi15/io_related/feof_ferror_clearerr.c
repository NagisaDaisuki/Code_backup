#include <stdio.h>
#include <stdlib.h>

#define FILENAME "status_demo.txt"

// 辅助函数：检查并报告文件状态
void report_status(FILE *fp, const char *message);

int main(void) {
  FILE *fp = NULL;
  int c;

  // 1. 创建并初始化文件
  fp = fopen(FILENAME, "w");
  if (fp == NULL)
    return EXIT_FAILURE;
  fputs("Hello C I/O.\n", fp);
  fclose(fp);

  // ===================================================================
  // 步骤 A: 正常读取直到 EOF (feof 示例)
  // ===================================================================

  fp = fopen(FILENAME, "r");
  if (fp == NULL)
    return EXIT_FAILURE;

  printf("1. 首次打开文件，指针位于开头。\n");
  report_status(fp, "状态A - 读取前");

  // 读取所有字符直到文件结束
  while ((c = fgetc(fp)) != EOF) {
    // 确保所有数据都被消耗
  }

  printf("\n2. 已读取文件所有内容(fgetc 返回 EOF)。\n");

  // 此时，文件指针越界，EOF标志被设置
  report_status(fp, "状态B - 读取到 EOF 之后");

  // ===================================================================
  // 步骤 B: 制造错误并清除 (ferror 和 clearerr 示例)
  // ===================================================================

  // 使用 fseek 强制将指针移动到文件末尾（但文件仍然是只读模式）
  // 尝试在只读文件上写入数据，在某些系统上会设置错误标志。
  fseek(fp, 0, SEEK_END);

  // 尝试写入数据，由于文件以 "r" 模式打开（只读），这将失败，并设置错误标志
  // 注意：虽然不能写入，但 ferror 通常在尝试一个非法操作后被设置。
  // 在本例中，我们尝试在只读文件上使用 fputc，它会失败并设置 ferror 标志。
  c = fputc('X', fp);

  // 检查 fputc 是否失败(通常返回 EOF)
  if (c == EOF) {
    printf("\n3. 尝试在只读流上写入数据(fputc)失败。\n");
  }

  // 此时，错误标志 ferror 被设置
  report_status(fp, "状态C - 尝试非法写入后");

  // clearerr 示例
  clearerr(fp);
  printf("4. 使用 clearerr() 清除了 EOF 和错误标志。\n");

  report_status(fp, "状态D - clearerr() 之后");

  fclose(fp);
  remove(FILENAME); // 清理文件

  return EXIT_FAILURE;
}

void report_status(FILE *fp, const char *message) {
  printf("\n--- %s ---\n", message);

  // feof(fp): 检测是否到达文件末尾
  if (feof(fp)) {
    printf("FE_EOF: 文件流已到达文件末尾 (EOF)。\n");
  } else {
    printf("FE_EOF: 文件流未到达文件末尾。\n");
  }

  // ferror(fp)：检测是否发生了 I/O 错误
  if (ferror(fp)) {
    printf("F_ERROR: 文件流发生 I/O 错误。\n");
  } else {
    printf("F_ERROR: 文件流状态正常。\n");
  }
}
