#include "stack.h"
#include <stdio.h>

int main(void) {
  Stack *myStack = createStack(5);

  printf("Is stack empty? %s\n", isEmpty(myStack) ? "Yes" : "No");

  push(myStack, 10);
  push(myStack, 20);
  push(myStack, 30);

  printf("Pop item %d\n", pop(myStack));
  printf("Pop item %d\n", pop(myStack));
  printf("Is stack empty? %s\n", isEmpty(myStack) ? "Yes" : "No");

  // 销毁栈并释放内存
  destroyStack(myStack);

  return 0;
}
