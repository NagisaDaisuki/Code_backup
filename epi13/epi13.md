# ☘️ 高级指针话题

## 13.1 进一步探讨指向指针的指针

- 二级指针的存在是为了间接访问指针元素（简单的赋值并不总是可行）

### 一个例子

~~~C
int i; 
int *p1;
int **ppi;
~~~

上面的声明在内存中创建了相应的变量。如果是自动变量则无法猜测初始值是多少。

~~~C
1. printf("%d\n",ppi);
2. printf("%d\n",&ppi);
3. *ppi = 5;
~~~

1. 如果`ppi`是一个自动变量，它就未被初始化，这条语句将打印一个随机值。如果它是一个静态变量，这条语句将打印0。
2. 这条语句把ppi的地址作为10进制打印，没有什么用。
3. 不可预测，对`pi`不应该执行初始化，因为它尚未被初始化。

> 对一个未被初始化的指针(野指针)进行解引用并向它所指向的随机内存地址写入值会导致未定义行为，极有可能触发**段错误(Segmentation Fault)**

~~~C
ppi = &pi;
*ppi = &i;
~~~

这两条语句把`pi`(通过`ppi`间接访问)初始化为指向变量`i`。

~~~C
i = 'a';
*pi = 'a';
**ppi = 'a';
~~~

这三条语句都可以对i进行赋值，但是简单的赋值并不总是可行。
> 如果想在一个自定义函数内修改调用者（如 main 函数）中声明的普通变量的值，需要传入该变量的一级指针。
如果想在自定义函数内释放外部函数中分配的动态内存，同时将外部的原始指针变量置为 NULL，则需要传入一个二级指针。

## 13.2 高级声明

### 几个例子

|函数|类型|
|:---:|:---:|
|int f|一个整型变量|
|int *f|一个指向整型的指针|
|int f|一个返回值为整型的函数|
|int *f()|一个返回值为指向整型的指针的函数|
|int (*f)()|一个指向返回值为整型的函数的指针|
|int *(*f)()|一个指向返回值为指向整型的指针的函数的指针|
|int f[]|一个整型数组|
|int *f[]|一个元素为指向整型的指针的数组|
|***int f()[]***|非法，f是一个函数，返回值是一个整型数组，但是函数只能返回标量值不能返回数组|
|***int f\[\]()***|非法，f是一个数组，它的元素类型是返回值为整型的函数，但数组元素必须有相同的长度，但不同的函数显然可能具有不同的长度|
|int (*f[])()|一个数组，数组的每个元素都是一个指针，该指针指向一个返回值为整型的函数|
|int *(*f[])()|一个数组，数组的每个元素都是一个指针，该指针指向一个返回值为指向整型的指针的函数|

带额外参数的函数定义

~~~C
int (*f)(int ,float);
int *(*g[])(int ,float);
~~~

## 13.3 函数指针

- 函数指针最常见的两个用途是 **转换表(jump table)** 和 **作为参数传递给另一个函数**。

> 简单声明一个函数指针并不意味着它可以立即使用。和其他指针一样对函数指针执行间接操作之前必须把它初始化为*指向某个函数*。

~~~C
int f(int);
int (*pf)(int) = &f;
~~~

初始化表达式中的`&`操作符是可选的，因为**函数名**被使用时总是由编译器把它转换为**函数指针**。
> int (*pf)(int) = f;
``
在函数指针被声明并且初始化后，就可以使用三种方式调用函数：

~~~C
int ans;
ans = f(25);
ans = (*pf)(25);
ans = pf(25);
~~~

上面第一种调用函数的方法其实是函数`f`首先被转换为一个函数指针，该指针指定函数在内存中的位置。然后，函数调用操作符调用该函数，执行开始于这个地址的代码。

后面两条函数调用操作和第一种是一样的。

### 13.3.1 回调函数

一个用于在单链表中查找一个值的函数，参数是一个指向链表第一个节点的指针以及那个需要查找的值

~~~C
Node*
search_list (Node *node, int const value)
{
  while (node != NULL)
  {
    if (node->value == value)
      break;
    node = node->link;
  }
  return node;
}
~~~

这个函数只适用于值为整数的链表。如果需要在一个字符串链表中查找不得不编写另一个函数且内容和这个函数类似。

一个更通用的方法是使查找函数与类型无关，这样它就能用于任何类型的值的链表。使用**函数指针**解决对多种节点类型的比较，将函数指针作为参数传入函数内执行比较操作。

我们无法在这个上下文环境中为回调函数编写一个准确的原型，因为我们并不知道进行比较的值的类型。事实上，我们需要查找函数能作用于任何类型的值。解决这个难题的方法是把参数类型声明为`void*`，表示“一个指向未知类型的指针”。

> 在使用比较函数中的指针之前，它们必须被强制转换为正确的类型。因为强制类型转换能够躲过一般的类型检查，所以在使用时必须额外小心，确保函数的参数类型是正确的。

一种实现方法

~~~C
/*
  在一个单链表中查找一个指定值的函数，它的参数是一个指向链表第一个节点的指针，
  一个指向我们需要查找的值的指针和一个函数指针，它所指向的函数用于比较存储于链表中类型的值。

  这里node未被声明为const，如果node被声明为const，函数将不得不返回一个const结果，
  这将限制调用程序，它变无法修改查找函数所找到的节点。
*/
#include <stdio.h>
#include "node.h"

Node*
search_list(Node *node, void const *value, int (*compare)(void const *, void const*))
{
  while (node != NULL)
  {
    if (compare(&node->value, value) == 0)
      break;
    node = node->link;
  }
  return node;
}
~~~

一个可用的int类型比较函数

~~~C
int compare_ints(void const *a, void const *b)
{
  if (*(int*)a == *(int*)b)
    return 0;
  else 
    return 1;
}
~~~

对字符串链表可用的查找

~~~C
#include <string.h>
...
desired_node = search_list(root, "desired_value", strcmp);
// int strcmp (const char *s1, const char *s2);
~~~

库函数`strcmp`所执行的比较和我们需要的完全一样，不过有些编译器会发出警告信息，因为它的参数被声明为`char*`而不是`void*`。

### 13.3.2 转移表

一个袖珍式计算器：具体操作和选择操作的代码分离

~~~C
double add(double,double);
double sub(double,double);
double mul(double,double);
double div(double,double);

switch(oper)
{
  case ADD:
    result = add(op1, op2);
    break;
  case SUB:
    result = sub(op1, op2);
    break;
  case MUL:
    result = mul(op1, op2);
    break;
  case DIV:
    result = div(op1, op2);
    break;
  default:
    break;
}
~~~

使用转换表实现计算机：声明函数指针数组并确保`add`，`sub`这些函数在函数指针数组前声明

~~~C
double (*oper_func[])(double, double) = {
  add, sub, mul, div, ...
};

result = oper_func[oper](op1, op2);
~~~

`oper`从数组中选择正确的函数指针，而函数调用操作符将执行这个函数。
> 在转换表中越界下标引用和使用其他数组一样是不合法的。

> 函数指针数组是 C 语言中实现分发逻辑（Dispatching）和状态机的一种强大机制。它允许你通过数组索引来调用不同的函数。
>> 可以使用`typedef`简化函数指针数组

~~~C
// 1. 定义函数指针类型： FuncPtr
typedef double (*FuncPtr)(double, double);
// 2. 使用 typedef 后的类型声明数组
FuncPtr oper_func[] = {add, sub, mul, div};
result = oper_func[oper](op1, op2);
~~~

## 13.4 命令行参数

处理命令行参数可以使用指针的指针

### 13.4.1 传递命令行参数

C程序的main函数具有两个形参，通常称为`argc`和`argv`

~~~C
int main (int argc, char **argv);
int main (int argc, char **argv);
~~~

1. `argc`存储一个整数值，表示程序在命令行被调用时，参数的总数量。这个数量包括程序本身的名称（可执行文件名），argc的值总是大于等于1
2. `argv`用于访问用户在命令行输入的具体字符串参数。

~~~C
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char **argv)
{
  //1. 打印参数总数
  printf("总共参数数量：%d\n",argc);
  
  // 2. 遍历所有参数
  printf("所有参数：\n");
  for (int i = 0; i < argc; i++)
    // argv[i] 是一个 char* 直接用 %s 打印字符串
    printf("argv[%d]: %s\n", i, argv[i]);
  
  // 3. 检查特定参数（检查是否提供了-v选项）
  for (int i = 1; i < argc; i++)
  {
    if (strcmp(argv[i],"-v") == 0)
      printf("\n检测到详细(verbose)模式。\n");
  }

  return 0;
}
~~~

终端执行(传递命令行参数)

~~~shell
gcc -Wall -std=c11 -g ***.c -o ***
./*** arg1 arg2 arg3 ... -v
~~~

一个**echolike**程序的c代码

~~~C
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char **argv)
{
  // 打印参数，直到遇到NULL指针，程序名被跳过
  while (*++argv != NULL)
    printf("%s\n", *argv);
  return EXIT_SUCCESS;
}
~~~

### 13.4.2 打印命令行参数

更通用的命令行参数处理(区分选项参数和文件名参数)

~~~C
#include <stdio.h>
#define TRUE 1

// 执行实际任务的函数的原型 
void process_standard_input(void);
void process_file(char *file_name);

// 选项标志，缺省初始化为FALSE
int option_a, option_b;

void main(int argc, char **argv)
{
  // 处理选项参数：跳到下一个参数并检查它是否以一个横杠开头
  while (*++argv != NULL && **argv == '-')
  {
    // 检查横杠后面的字母
    switch (*++*argv)
    {
      case 'a':
        option_a = TRUE;
        break;
      case 'b':
        option_b = TRUE;
        break;
    }
  }

  // 上面的代码可以被下面的替代
  // while ((opt = *++*argv) != '\0')
  // {
  //   switch (opt){
  //     case 'a':
  //       option_a = TRUE;
  //       break;
  //   }
  // }

  // 处理文件名参数
  if (*argv == NULL)
      process_standard_input();
  else{
    do{
      process_file(*argv);
    }while(*++argv != NULL);
  }
}
~~~

## 13.5 字符串常量

- 当一个字符串常量出现在表达式中时，它的值是一个指针常量。编译器把这些指定字符的一份拷贝存储在内存的某个位置，并存储一个指向第一个字符的指针。但是当数组名用于表达式时，它们的值也是指针常量。我们可以对它们进行下标引用、间接引用以及指针运算。

~~~C
"xyz" + 1
~~~

第一眼可能认为这个表达式毫无意义，但只要把字符串常量看作指针时，它的意义就非常清楚了。这个表达式计算“指针值加上1”的值。它的结果是个指针，指向字符串中的第二个字符:`y`

那么这个表达式又是什么呢？

~~~C
*"xyz"
~~~

如果`xyz`是一个“指向字符的指针”，那么这个间接访问的结果就是它所指向的字符`x`

一个另类的字符`z`的表达式

~~~C
"xyz[2]
~~~

一个偏移量超出字符串范围的表达式，这个表达式的结果就是一个不可预测的字符

~~~C
*("xyz" + 4)
~~~

什么时候人们可能想使用类似上面的这些形式的表达式呢？

~~~C
// 把二进制值转换为字符并把他们打印出来。
void binary_to_ascii(unsigned int value)
{
  unsigned int quotient;
  
  quotient = value / 10;
  if (quotient != 0)
    binary_to_ascii(quotient);
  putchar(value % 10 + '0');
}
~~~
