#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define SIZE 20

int main(void) {
  char buffer[SIZE] = {};
  int front, rear;
  printf("Please input a string less than 20 characters:\n");

  // === 修正问题1：正确使用 fgets ===
  // fgets 的第二个参数应该是缓冲区大小，而不是字符串长度
  fgets(buffer, SIZE, stdin);

  // === 修正问题2：正确初始化 rear ===
  // 初始化 rear 应该在 fgets 之后
  // 并且去除 fgets 读取的换行符 '\n'，否则会影响判断
  rear = strlen(buffer) - 1;
  if (rear >= 0 && buffer[rear] == '\n') {
    buffer[rear] = '\0';
    rear--; // 重新计算 rear
  }

  front = 0;

  // 非指针回文数验证
  while (front < rear) {
    if (buffer[front] != buffer[rear])
      break;
    front += 1;
    rear -= 1;
  }
  if (front >= rear)
    printf("It is a palindrome!\n");
  else
    printf("It is not a palindrome!\n");

  // --- 分隔线 ---

  // 指针回文数验证
  // 重新初始化指针，因为它们在上一段代码中被修改了
  char *bufferPtrFront = buffer;

  // 重新计算 rear 的位置
  // 在上一个代码块中，rear 已经被修改了
  rear = strlen(buffer) - 1;
  char *bufferPtrRear = buffer + rear;

  while (bufferPtrFront < bufferPtrRear) {
    if (*bufferPtrFront != *bufferPtrRear)
      break;
    bufferPtrFront++;
    bufferPtrRear--;
  }
  if (bufferPtrFront >= bufferPtrRear)
    printf("\nIt is a palindrome!");
  else
    printf("\nIt is not a palindrome!");

  printf("\n");

  return EXIT_SUCCESS;
}
