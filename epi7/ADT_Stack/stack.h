#ifndef STACK_H
#define STACK_H

// 定义栈的抽象类型
// 用户只需要知道有这个类型，但不知道它的具体结构

typedef struct StackType Stack;

// 初始化一个栈并返回其指针。
Stack *createStack(int capacity);

// 销毁一个栈，释放内存。
void destroyStack(Stack *s);

// 将一个元素压入栈顶。
void push(Stack *s, int item);

// 从栈顶弹出一个元素。
int pop(Stack *s);

// 检查栈是否为空
int isEmpty(Stack *s);

#endif
