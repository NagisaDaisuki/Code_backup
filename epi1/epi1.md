<h3><center>快速上手</center></h3>

-----------
#### 1.1.1 空白和注释
1. 遵守一些规定会让C语言代码变得更加容易阅读和修改
2. 注释告诉读者程序能做些什么
3. 使用#if和#endif预处理有效地将代码从程序中去除
~~~
#if 0       //条件(真执行，假不执行)
    statements
#endif
~~~

#### 1.1.2 预处理指令
~~~
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX_COLS 20
#define MAX_INPUT 1000 
~~~
| 这五行被称为预处理指令，因为它们是由预处理器解释的。

~~~
int read_column_numbers(int columns[], int max);
void rearrange(char *output, char const *input,
                int n_columns, int const columns[]);
~~~
| 这些声明被称为**函数原型(function prototype)**。它告诉编译器这些以后将在源文件中定义的函数的特征。

#### 1.1.3 main函数
**每个C程序都必须有一个main函数，因为它是程序执行的起点。**

<code>n_columns = read_column_numbers(columns,MAX_COLS);</code>

> 这条语句调用函数read_column_numbers。数组columns和MAX_COLS代表的常量20作为参数传递给这个函数。在C语言中，数组参数是以 **引用(reference)** 传递的，也就是传址调用，而标量和常量则是按 **值(value)** 传递的。

#### 1.1.4 关于scanf的格式代码
常用的scanf格式代码除了`%c,%s`以外在输入值前的空白都会被省略。所以在使用scanf函数中的格式代码%c,%s输入时不能在输入值前有空格、换行和tab
