#include "stack.h"
#include <stdio.h>
#include <stdlib.h>

// 栈的内部表示 (数据隐藏)
// 这个结构体只在该文件中可见

struct StackType {
  int *array;
  int top;
  int capacity;
};

// 创建APT栈
Stack *createStack(int capacity) {
  Stack *s = (Stack *)malloc(sizeof(struct StackType));
  if (s == NULL) {
    // Handle memory allocation failure.
    return NULL;
  }
  s->capacity = capacity;
  s->top = -1; // -1 表示栈为空
  s->array = (int *)malloc(capacity * sizeof(int));

  if (s->array == NULL) {
    // Handle memory allocation failure.
    free(s);
    return NULL;
  }
  return s;
}

// 销毁ADT栈，先销毁栈结构体内的动态数组
void destroyStack(Stack *s) {
  if (s != NULL) {
    free(s->array);
    free(s);
  }
}

// 压入数据到ADT栈
// 先检测栈是否已满
// 后压入栈
void push(Stack *s, int item) {
  if (s->top < s->capacity - 1) {
    s->array[++s->top] = item;
  } else {
    printf("Error: Stack overflow!\n");
  }
}

// 从ADT栈弹出数据
int pop(Stack *s) {
  if (!isEmpty(s)) {
    return s->array[s->top--];
  } else {
    printf("Error: Stack is empty!\n");
    return -1; // 返回一个错误值
  }
}

// 判断是否为空
int isEmpty(Stack *s) { return s->top == -1; }
