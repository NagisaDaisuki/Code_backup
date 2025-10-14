/*
 *  定义一个不易发生错误的内存分配器。
 * */
#include <stdio.h>

#define malloc
#define MALLOC(num, type) (type *)alloc((num) * sizeof(type))
extern void *alloc(size_t size);
