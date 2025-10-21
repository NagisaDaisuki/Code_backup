# 🍋‍🟩 预处理器

编译一个C程序涉及很多步骤。其中第一个步骤被称为**预处理(preprocessing)阶段**。C预处理器在源代码编译之前对其进行一些文本性质的操作。它的主要任务包括删除注释、插入被`#include`指令包含的文件的内容、定义和替换由`#define`指令定义的符号以及确定代码的部分内容是否应该根据一些条件编译指令进行编译。

## 14.1 预定义符号

|**符号**|**样例值**|**含义**|
|:---:|:---:|:---:|
|\_\_FILE\_\_|"name.c"|进行编译的源文件名|
|\_\_LINE\_\_|25|文件当前行的行号|
|\_\_DATE\_\_|"Jan 31 1997"|文件被编译的日期|
|\_\_TIME\_\_|"18:04:30"|文件被编译的时间|
|\_\_STDC\_\_|1|如果编译器遵循ANSI C，其值就为1，否则未定义|

`__FILE__`和`__LINE__`在确认调试输出的来源方面很有用处。`__DATE__`和`__TIME__`常常用于在被编译的程序中加入版本信息。`__STDC__`用于那些在ANSI环境和非ANSI环境都必须进行编译的程序中结合条件编译。

**更多实用的预定义符号**

|**符号**|**样例值**|**含义**|
|:---:|:---:|:---:|
|\_\_STDC\_VERSION\_\_|202311|显示编译器当前版本号|
|\_\_func\_\_|main|显示当前所在函数函数名|
|\_\_GUNC\_\_|15|和下面两个预定义符号一起使用，显示gcc当前符号|
|\_\_GUNC\_MINOR\_\_|2|同上|
|\_\_GUNC\_PATCHLEVEL\_\_|1|同上|
|\_\_OPTIMIZE\_\_|1|判断是否使用code optimization|
|\_\_x86\_64\_\_|1|判断系统芯片架构，下面一致|
|\_\_i386\_\_|1|同上|
|\_\_aarch64\_\_|1|同上|
|\_\_arm\_\_|1|同上|
|\_\_powerpc64\_\_|1|同上|
|\_\_powerpc\_\_|1|同上|

## 14.2 #define

在一些简单的用法中`#define`就是为数值命名一个符号

`#define`更为正式的描述

~~~C
#define name stuff
~~~

替换文本并不限于数值字面值常量。使用`#define`指令，你可以把任何文本替换到程序中。

~~~C
#define reg         register
#define do_forever  for(;;)
#define CASE        break;case
~~~

如果定义中的stuff非常长，它可以分成几行，除了最后一行之外，每行的末尾都要加一个反斜杠。

~~~C
#define DEBUG_PRINT(x,y,z)   printf( "File %s line %d:" \
                             " x=%d, y=%d, z=%d", \
                             __FILE__, __LINE__, \
                             x, y, z ) 
~~~

这里使用了相邻的字符串常量被自动连接为一个字符串的这个特性。
> #define 语句末尾不需要加分号`;`
还可以使用`#define`指令把一序列语句插入到程序中。

~~~C
#define PROCESS_LOOP \
        for (i = 0; i < 10; i += 1){  \
            sum += i;                 \
            if (i > 0)                \
            prod *= i;                \
        }
~~~

> 不要滥用这种技巧，如相同的代码需要出现在程序的几个地方，函数是一个更好的实现办法。

### 14.2.1 宏

- #define 机制包括了一个规定，允许把参数替换到文本上，这种实现通常称为 **宏(macro)** 或定义宏(defined macro)

~~~C
#define name(parameter-list) stuff
~~~

`parameter-list(参数列表)`是一个由逗号分隔的值的列表，每个值都与宏定义中的一个参数相对应

~~~C
// 一个接受一个参数的宏
#define SQUARE(x) x * x

// 正常使用没有问题
SQUARE(5) // 返回值是 25

// 下面是这个定义的问题
int a;
a = 5; 
printf("%d\n",SQUARE(a + 1));
// 这里返回值返回 11 而不是 36

// 被替换宏文本
printf("%d\n", a + 1 * a + 1);
// 根据四则运算先执行 1 * a 后执行两个加法
// 修改为
#define SQUARE(x) (x) * (x)
// 这样就可以避免第一个问题

// 另一个问题
#define DOUBLE(x) (x) + (x)
a = 5;
printf("%d\n", 10 * DOUBLE(a));
// 这里返回的是 55 而不是 100
printf("%d\n", 10 * (a) + (a));
// 在原来的定义外添加一个括号
#define DOUBLE(x) ((x) + (x))
// 就可以解决这个问题
~~~

> 所有用于对数值表达式进行求值的宏定义都应该用这种方式加上括号

**一种有趣的宏**

~~~C
#define repeat do
#define until(x) while(!(x))

// 上面的宏定义将下面的循环替换

// 替换
do{
  statements;
}while(!(i >= 10));

// 为
repeat {
  statements;
} until (i >= 10);
~~~

> 应该避免一直使用这种写法
>
### 14.2.2 #define 替换

1. 在调用宏时，首先对参数进行检查，看看是否包含了任何由`#define`定义的符号。如果是，它们首先被替换。
2. 替换文本随后被插入到程序中原来文本的位置。对于宏，参数名被他们的值所替代。
3. 最后，再次对结果文本进行扫描，看看它是否包含了任何由`#define`定义的符号。如果是就重复上述处理过程。

这样宏参数和`#define`可以包含其他`#define`定义的符号。但是宏不可以出现递归。

- 当预处理器搜索`#define`定义的符号时，字符串常量的内容并不进行检查。有两种将宏参数插入到字符串常量的方法

~~~C
#define PRINT(FORMAT, VALUE) \
      printf( "The value is " FORMAT "\n", VALUE)
... 
PRINT("%d", x + 3)
~~~

> 这种技巧只有当字符串常量作为宏参数给出时才能使用

~~~C
#define PRINT(FORMAT, VALUE) \
    printf( "The value of " #VALUE \
    " is " FORMAT "\n", VALUE )
...
PRINT( "%d", x + 3 ) // The value of x + 3 is 25 
~~~

- 第二个技巧使用预处理器把一个宏参数转换为一个字符串。`#argument`这种结构被预处理器翻译为`argument`。

- `##`结构则执行一种不同的任务。它把位于它两边的符号连接成一个符号。作为用途之一，它允许宏定义从分离的文本片段创建标识符。

~~~C
#define ADD_TO_SUM ( sum_number, value ) \
    sun ## sum_number += value
... 
ADD_TO_SUM( 5, 25 );
// 这条语句的意思是 sum5 += 25; 这种连接必须产生一个合法的标识符。否则其结果就是未定义的。
~~~

### 14.2.3 宏与函数

~~~C
#define MAX(a,b) ((a) > (b) ? (a) : (b))
~~~

使用宏来定义简单计算而不是函数有两个优点：

1. 用于调用和从函数返回的代码可能比实际执行这个小型计算工作的代码更大，所以对于简单函数使用宏比使用函数在***程序的规模和速度方面都更胜一筹***。
2. 函数的参数必须声明一种特定的类型，上面这个宏定义可以用于整型、长整型、单浮点型、双浮点型等其他的类型。***宏是与类型无关的***。

还有一些任务无法用函数实现只能用宏定义实现。

~~~C
#define MALLOC(n, type) \ 
    ( (type*)malloc( (n) * sizeof(type)))
// 被转换为
pi = MALLOC(25, int);
pi = ((int*)malloc((25) * sizeof(int)));
~~~

> 请注意宏定义并没有用一个分号结尾。分号出现在调用这个宏的语句中。
>
### 14.2.4 带副作用的宏参数

当宏参数在宏定义中出现的次数超过一次时，如果这个参数具有副作用那么当你使用这个宏时就可能出现危险，导致不可预料的结果。**副作用**就是在表达式求值时出现的永久性效果。例如 :

~~~C
x + 1
~~~

可以重复执行几百次，它每次获得的结果都是一样的。这个表达式不具有副作用。但是：

~~~C
x++
~~~

就具有副作用：它增加`x`的值。当这个值在下一次执行时，它将产生不同的结果。

~~~C
#define MAX(a,b) ((a) > (b) ? (a) : (b))
...
x = 5;
y = 8;
z = MAX( x++, y++ );
printf("x=%d, y=%d, z=%d\n", x, y, z);
// MAX的结果执行后 x = 6, y = 10, z = 9
// 虽然那个较小的值只增加了一次，但那个较大的值却增加了两次(y++) ? (y++)
z = ((x++) > (y++) ? (x++) : (y++));
~~~

### 14.2.5 命名约定

为了区分宏定义和函数的区别需要一个**命名约定**，最明显的区别就是函数名一般用全小写字母，宏定义用全大写字母。

***宏和函数的不同之处***

|属性|#define宏|函数|
|:---:|:---:|:---:|
|代码长度|每次使用时，宏代码都被插入到程序中。除了非常小的宏之外，程序的长度将大幅度增长|函数代码之处限于一个地方；每次使用这个函数时，都调用那个地方的同一份代码|
|执行速度|更快|存在函数调用/返回的额外开销|
|操作符/优先级|宏参数的求值是在所有周围表达式的上下文环境里，除非它们加上括号，否则邻近操作符的优先级可能会产生不可预料的结果|函数参数只在函数调用时求值一次，它的结果值传递给函数。表达式的求值结果更容易预测|
|参数求值|参数每次用于宏定义时，它们都将重新求值。由于多次求值，具有副作用的参数可能会产生不可预测的结果|参数在函数被调用前只求值一次。在函数中多次使用参数并不会导致多种求值过程。参数的副作用并不会造成任何特殊的问题|
|参数类型|宏与类型无关。只要对参数的操作是合法的，它可以使用于任何参数类型|函数的参数是与类型有关的。如果参数的类型不同，就需要使用不同的函数，即使它们执行的任务是相同的|

### 14.2.6 #undef

- 这条预处理指令用于移除一个宏定义。

~~~C
#undef name
~~~

如果一个现存的名字需要被重新定义，那么它的旧定义首先必须用`#undef`移除。

### 14.2.7 命令行定义

许多C编译器提供了在命令行中定义符号，用于启动编译过程。

~~~C
int array[ARRAY_SIZE];

-Dname
-Dname=stuff

cc -DARRAY_SIZE=100 prog.c
~~~

## 14.3 条件编译

- 只用于调试程序的语句就是一个明显的例子它们不应该出现在程序的产品版本中，**但是你可能并不想把这些语句从源代码中物理删除，因为如果需要一些维护性修改时，你可能需要重新调试这个程序，还需要这些语句**。
- 条件编译(conditional compilation)就是用于实现这个目的。

~~~C
#if constant-expression
      statements
#endif
~~~

其中`constant-expression`（常量表达式）由预处理器进行求值。如果它的值是非零值（真），那么`statements`部分就被正常编译，否则预处理器就安静地删除它们。

~~~C
#define DEBUG 1
#if DEBUG
  printf(statements);
#endif
~~~

一个简单的使用条件编译

`#if`的子句`#elif`和`#else`

~~~C
#if constant-expression
      statements
#elif  constant-expression
      other statements ...
#else 
      other statements
#endif
~~~

### 14.3.1 是否被定义

~~~C
#if defined(symbol)
#ifdef symbol

#if !defined(symbol)
#ifndef symbol
~~~

`#if`形式的语句功能更强。因为常量表达式可能包含额外的条件

~~~C
#if X > 0 || defined(ABC) && defined(BCD)
~~~

> 一些老K&R C编译器并未包含所有功能。

### 14.3.2 嵌套指令

~~~C
#if defined( OS_UNIX )
  #ifdef OPTION1
  unix_version_of_option1();
  #endif
  #ifdef OPTION2
  unix_version_of_option2();
  #ifdef OPTION3
  unix_version_of_option3();
#elif defined( OS_MSDOS )
  #ifdef OPTION2
  msdos_version_of_option2();
  #endif
#endif
~~~

> 在每个#endif 后添加一个注释标签可以很好地区分每个嵌套的指令

## 14.4 文件包含

- 一个头文件如果被包含到10个源文件中，它实际上被编译了10次。

> 但实际上这种额外开销实际上并不大。
>
### 14.4.1 函数库文件包含

头文件包含语法

~~~C
#include <filename>
~~~

> UNIX 系统上使用`<>`包含的头文件一般在目录`/usr/include`查找
>> 编译器有一个选项`-I`允许把其他目录添加到这个列表中
>>
### 14.4.2 本地文件包含

~~~C
#include "filename"
~~~

> 优先从.c文件或.h文件所在的当前目录查找
>
### 14.4.3 嵌套文件包含

~~~C
#include "a.h"
#include "b.h"
// 如果b.h 文件里包含了a.h，那么a.h在当前文件就被包含了两次
--------
// another file
#ifndef _HEADERNAME_H
#define _HEADERNAME_H 1 // #define _HEADERNAME_H
// All the stuff that you want in the header file
#endif

// 使用这种方法并不能直接不调用第二次该文件，但是文件内的所有文件会在第二次调用被弃用
~~~

> 这种处理将拖慢编译速度，所以可能尽量避免出现多重包含

## 14.5 其他指令

### 14.5.1 #error

当程序编译之后，`#error`指令允许你生成错误信息，并强制终止编译过程。

~~~C
#error text of error message
// 使用案例
#if defined(OPTION_A)
    stuff needed for optionA
#elif defined(OPTION_B)
    stuff needed for optionA
#elif defined(OPTION_C)
    stuff needed for optionC
#else
    #error No option selected!
#endif

// 检查 C 标准版本
#if __STDC_VERSION__ < 199901L
#error "本项目要求 C99 或更高版本的编译器！"
#endif

#ifdef WINDOWS_ENV 
    // 针对 Windows的代码...
#elif defined(LINUX_ENV)
    // 针对 Linux的代码...
#else
#error "必须定义 WINDOWS_ENV 或 LINUX_ENV 宏以指定编译环境！"
~~~

### 14.5.2 #line

`#line`指令用于改变编译器对当前代码行号和文件名的追踪。

~~~C
#line number "string"
// number 将当前源代码行的行号设置为这个数字
// string 可选，将编译器追踪的文件名设置为这个字符串

// 例子
// 原始文件名 line.c  假设
#include <stdio.h>

int a = 1;

#define DEBUG 0
#undef DEBUG
// gcc -std=c11 -g -Wall -DDEBUG=0 line.c
// gcc -std=c11 -g -Wall -DDEBUG=1 line.c
// 使用-DNAME 控制定义名的值
#if DEBUG
#line 100 "generated_code.c"
#endif
void func() {
  int b = 2;       // 编译器现在认为这是 generated_code.c 的 101 行
  int c = "error"; // 故意制造一个错误
}

// 恢复到当前文件的实际行号
#line __LINE__

int main(void) {
  func();
  return 0;
}
~~~

### 14.5.3 #progma

- 一种特殊的预处理器指令，用于向编译器发出特殊指令或特定于实现的功能。
- `#progma` 的行为完全取决于编译器。

~~~C
#progma 记号序列
// -------------
#progma once // 非标准但广泛使用，确保头文件只被编译一次，防止重复包含错误。
// 不是C标准的一部分，但是几乎所有的现代编译器(GCC, Clang, MSVC)都支持。
#progma STDC // C99/C11 标准用于控制浮点运算和线程。

#progma pack(n) // 控制结构体对齐
// 改变结构体的内存对齐方式
struct DefaultStruct {
  char c;
  int i; // 4 字节，可能有三字节的填充
};

// 设置对齐为 1字节
#progma pack(push, 1)

struct PackedStruct {
  char c; // 1字节
  int i; // 4 字节，紧跟在 c 之后，没有填充
};

#progma pack(pop) // 恢复默认对齐设置
~~~
