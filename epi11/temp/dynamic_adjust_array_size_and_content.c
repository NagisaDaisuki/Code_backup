#include <stdio.h>
#include <stdlib.h>
#include <string.h> // 需要用 memset 演示 calloc 的初始化特性

// 定义一个常量用于内存大小
#define INITIAL_SIZE 5
#define EXTENDED_SIZE 10

void dynamic_memory_demo();

int main(void) {
  dynamic_memory_demo();
  return 0;
}

void dynamic_memory_demo() {
  int *arr = NULL;
  int i;

  printf("--- 1. malloc：首次分配内存 ---\n");
  // 1. malloc：分配 5 个 int 类型的空间
  // (sizeof(int) * INITIAL_SIZE) = 4 字节 * 5 = 20 字节
  arr = (int *)malloc(sizeof(int) * INITIAL_SIZE);

  // 注意事项 1: 检查 malloc 是否分配成功
  if (arr == NULL) {
    perror("malloc 分配失败");
    return;
  }
  printf("malloc 成功分配 %d 个 int 的空间，地址：%p\n", INITIAL_SIZE,
         (void *)arr);

  // 注意事项 2: malloc 不初始化内存，内容是随机的
  for (i = 0; i < INITIAL_SIZE; i++) {
    arr[i] = 10 + i;
    printf("arr[%d] = %d (初始化值)\n", i, arr[i]);
  }

  printf("\n--- 2. calloc: 演示初始化特性 ---\n");
  // 为了演示 calloc 的初始化特性，先释放arr，再用 calloc 重新分配
  free(arr);
  arr = NULL; // 置空指针

  // calloc: 分配 5 个 int 类型的空间，并全部初始化为 0
  arr = (int *)calloc(INITIAL_SIZE, sizeof(int));

  if (arr == NULL) {
    perror("calloc 分配失败");
    return;
  }
  printf("calloc 成功分配 %d 个 int 的空间，地址：%p\n", INITIAL_SIZE,
         (void *)arr);
  printf("calloc 自动将内存初始化为 0:\n");

  // 重新写入数据，为下一步 realloc 做准备
  for (i = 0; i < INITIAL_SIZE; i++) {
    arr[i] = i;
  }

  printf("\n--- 3. realloc: 扩大数组空间 ---\n");
  // realloc: 将数组扩大到 10 个 int 类型的空间
  // 注意事项 3: realloc 的最佳实践是使用一个临时指针

  int *temp = (int *)realloc(arr, sizeof(int) * EXTENDED_SIZE);

  if (temp == NULL) {
    perror("realloc 失败，数据不变");
    // 如果 realloc 失败，arr 指向的旧内存块仍然有效，不应丢失。
    // 此时我们不做任何处理，继续使用 arr。
  } else {
    // 如果 realloc 成功，更新指针
    arr = temp;
    printf("realloc 成功扩大到 %d 个 int 的空间，新地址：%p\n", EXTENDED_SIZE,
           (void *)arr);

    // 注意事项 4: realloc 会保留旧数据，但新增部分未初始化
    printf("保留的旧数据 ( 0 - 4 ):\n");

    for (i = 0; i < INITIAL_SIZE; i++) {
      printf("arr[%d] = %d\n", i, arr[i]);
    }

    printf("新增的内存部分 (5-9) 是未初始化的:\n");
    for (i = INITIAL_SIZE; i < EXTENDED_SIZE; i++) {
      printf("arr[%d] = %d(随机值)\n", i, arr[i]);
      arr[i] = i * 2; // 赋新值
    }
  }

  printf("\n--- 4. free: 释放内存 ---\n");
  // free: 释放 arr 指向的整个内存块
  free(arr);

  // 注意事项 5: 避免野指针，将指针设置为NULL
  arr = NULL;
  printf("内存已经释放。arr 指向 NULL：%p\n", (void *)arr);

  // 注意事项 6: 避免二次释放
  // 错误示例：free(arr); // 再次调用会导致程序崩溃或未定义行为
}
