# 😠 函数

## 7.1 函数定义

- 函数的定义就是**函数体的实现**:
- 函数体就是一个**代码块**，它在函数被调用时执行:

~~~shell
类型
函数名( 形式参数 )
代码块

function_name()
{

}
~~~

**存根(stub)**：为那些此时尚未实现的代码保留一个位置。

> **K&R C**形参声明

~~~shell
int *
find_int(key, array, array_len)
int key;
int array[];
int array_len;
{}
~~~

**return语句**

- return语句允许从函数体的*任何位置*返回。
- return expression中的`expression`是可选的。
- 通常，表达式的类型就是函数声明的返回类型。

> 没有返回值或`return;`的函数类型应该设置为void函数。
>> 函数被分为有返回值的函数(**真函数**)和没有返回值的函数(**过程或副作用**)。

## 7.2 函数声明

- 使用 ***函数原型(function prototype)*** 为编译器提供函数的完整信息:
- 对于*K&R C*风格函数编译器只知道函数返回值类型:

> 标准表示，在同一个代码块中，函数原型必须与**同一个函数**的**任何先前原型**匹配。

### 7.2.2 函数的缺省认定

- 无法见到原型的函数，编译器认为该函数返回值为整数类型。

## 7.3 函数的参数

- C函数的所有参数均以 **"传值调用"** 方式进行传递，即传递参数的副本。
- 传递指针和数组的行为实际上为 **"传址调用"** 。

> 对指针和数组进行*间接访问操作*。

**缺省参数提升**：使用K&R C旧风格的形参类型*类似char 和 short类型*会被提升为`int`类型,*float类型*会被提升为`double`类型

## 7.4 ADT和黑盒

- C语言可以用于设计和实现**抽象数据类型(ADT, Abstract Data Type)**，因为它可以***限制***函数和数据定义的作用域。

- **抽象数据类型(ADT, Abstract Data Type)** 是一种编程概念，它将数据的表示(如何存储)和对数据的操作(如何使用)分离开来。

### ADT的核心思想

1. **数据隐藏(Data Hiding)**：数据的具体存储方式被隐藏起来，外部代码无法直接访问或修改。

2. **接口(Interface)**：ADT提供一组明确定义的公共函数，作为与外部世界的唯一交互方式。

- 限制对模块的访问是通过合理使用`static`关键字来实现的，它可以限制对那些并非接口的函数和数据的访问。

### 示例：一个简单的计数器模块

`counter.h`(公共接口)

这是模块的”对外合同“，它只声明了其他文件可以访问的公共函数。

~~~shell
#ifndef COUNTER_H
#define COUNTER_H

// Increment the counter by 1.
void increment_counter(void);

// Get the current value of the counter. 
int get_counter(void);
#endif // COUNTER_H
~~~

`counter.c`(黑盒实现)

这是模块的”内部黑盒“。`static`关键字使得`count`变量和`private_helper`函数无法被其他文件直接访问。

~~~shell
#include "counter.h"
#include <stdio.h>
// This is a static variable. Its value is kept for the lifetime of the program,
// but it is only visible and accessible within this file (counter.c).
static int count = 0;

// This is a static function. It's a private helper and cannot be called
// from outside this file.
static void private_helper()
{
  printf("--- (Internal) The counter is now being updated... ---\n");
}

// Public API function. It calls the private helper function
void increment_counter()
{
  private_helper(); // This is allowed bacause private_helper is in the same file.
  count++;
}

// Public API function. It returns the value of the private variable.
int get_counter()
{
  return count;
}
~~~

`main.c`(使用模块)

这个文件只能通过`counter.h`中声明的公共函数与`counter.c`交互。任何试图访问内部私有函数的行为都将导致编译或链接错误。

~~~shell
#include <stdio.h>
#include "counter.h"

int main()
{
  printf("Initial counter value: %d\n",get_counter());
  
  // Call the public function to increment the counter.
  increment_counter();
  printf("Counter value after first increment: %d\n", get_counter());

  increment_counter();
  printf("Counter value after second increment: %d\n", get_counter());

  // COMPILE/LINK ERROR!
  // The linker will fail because private_helper() is not a public symbol.
  // private_helper(); 

  return 0; 
}
~~~

> 如果不包含最后一行`private_helper()`的调用程序将编译和链接成功。

## 7.5 递归

- 递归函数就是直接或间接调用自身的函数。
- C通过**运行时堆栈**支持递归函数的实现。
- 递归的效率大部分情况下都非常低。

### 使用递归与迭代来表示阶乘的计算

~~~shell
factorial(n) =
├── n <= 0 : 1
└── n > 0 : n x factorial(n - 1)
~~~

**递归方法**

~~~shell
long 
factorial(int n)
{
  if (n <= 0)
    return 1;
  else 
    return n * factorial(n - 1);
}
~~~

**迭代方法**

~~~shell
long
factorial(int n)
{
  int result = 1;
  while (n > 1)
  { 
    result *= n;
    n -= 1;
  }
  
  return result;
}
~~~

> 许多问题是以递归的形式进行解释的，这只是因为它比非递归形式更为清晰，但是这些问题的迭代实现往往比递归实现效率更高。

### 使用递归与迭代来表示斐波那契数

~~~shell
Fibonacci(n) =
├── n <= 1 : 1 
├── n = 2 : 1
├── n > 2 : Fibonacci(n - 1) +Fibonacci(n - 2)
~~~

**递归方法**

~~~shell
long fibonacci(int n)
{
  if (n <= 2)
    return 1;

  return fibonacci(n - 1) + fibonacci(n - 2);
}
~~~

**迭代方法**

~~~shell
long fibonacci(int n)
{
  long result;
  long previous_result;
  long next_older_result;
  
  result = previout_result = 1;
  
  if (n <= 2)
    return 1;
  
  while (n > 2)
  {
    n -= 1;
    next_older_result = previous_result;
    previous_result = result;
    result = previous_result + next_older_result;
  }
}
~~~

> 使用递归实现斐波那契数的代价比你远想的要大。

## 7.6 可变参数列表

- 使用`stdarg`宏实现可变参数列表，这些宏定义在`stdarg.h`头文件
- 在定义可变参数列表时在省略号前一定是代表后面可变参数列表**参数个数**

这个头文件声明了一个类型`va_list`和3个宏---`va_start`、`va_arg`和`va_end`

### 计算标量参数平均值(非可变参数)

~~~shell
float average(int n_values, int v1,int v2, int v3, int v4, int v5)
{
  float sum = v1; 
  
  if ( n_values >= 2)
    sum += v2;
  if ( n_values >= 3 )
    sum += v3;
  if ( n_values >= 4 )
    sum += v4;
  if ( n_values >= 5 )
    sum += v5;

  return sum / n_values;
}
~~~

### 计算标量参数平均值(可变参数)

~~~shell
#include <stdarg.h>

float average(int n_values, ...) // 传递任意数量的未知数
{
  va_list var_arg;
  int count;
  float sum;
  
  // 准备访问可变参数
  va_start (var_arg, n_values);
  
  // 添加取自可变参数列表的值
  for (count = 0;count < n_values;count += 1)
    sum += va_arg(var_arg, int);
  
  // 完成处理可变参数
  va_end(var_arg);
  
  return sum / n_values;
}
~~~
