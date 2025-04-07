<h3><center>数据</center></h3>

------

#### 3.1 基本数据类型
- 在C语言中，只有四种基本数据类型：**整形、浮点型、指针和聚合类型(数组和结构)**
> 字符型是整型的一种

#### 3.1.1 整型家族
分为字符型、短整型、整型和长整型，且分为有符号(signed)和无符号(unsigned)
- **长整型至少应该和整型一样长，整型至少应该和短整型一样长。**
- 如果显示地把变量声明为signed或unsigned可以提高这类程序的可移植性。

1.整型字面值

**字面值(literal)** 这个术语是字面值常量的缩写————这是一种实体，指定了自身的值并且不允许发生改变。所以ANSI C允许 **命名常量const**

在整数值后面添加l或L将整数解释为长整型值、u或U将数值指定为unsigned整型值。ul和UL就是这两个的结合

对于多字节字符如果一个多字节字符常量的前面有一个L那么它就是**宽字符常量(wide character literal)**如：
`L'X' L'e^'`

不管采用何种字符集，使用字符常量所产生的总是正确的值，所以字符常量能提高程序的可移植性

2.枚举类型

**枚举(enumerated)类型**就是指它的值为符号常量而不是字面值的类型
~~~
enum Jar_Type { CUP, PINT, QUART, HALF_GALLON, GALLON}; //声明了一个enum类型称为Jar_Type
enum { CUP, PINT, QUART, HALF_GALLON, GALLON} milk_jug,gas_can; // 匿名枚举类型并直接定义枚举类型变量 milk_jug,gas_can
enum Jar_Type { CUP = 8, PINT = 10, QUART = 11, HALF_GALLON, GALLON};
// 根据enum赋值规律，HALF_GALLON的值为12，GALLON为13
~~~

#### 3.1.2 浮点类型
浮点数字面值在缺省情况下都是double类型的，后跟L为long double，跟F为float

#### 3.1.3 指针
1. 指针常量

指针常量只能通过已分配的内存的元素得知。</br>
因此，把指针常量表达为数值字面值的形式几乎没有用处。

2. 字符串常量

可以把字符串常量赋值给一个指向字符类型的数组char* </br>
不能把字符串常量赋值给一个字符数组char[]

#### 3.2 基本声明

变量声明的基本形式是：`说明符(一个或多个) 声明表达式列表`

`int* a,b,c和int *a,*b,*c`是在声明指针时非常容易搞混的两个概念，为避免概念上的错误建议将*号写在靠近变量名那一侧

#### 3.2.4 隐式声明
一条语句实际上是一个声明时，如果它缺少类型名，编译器会假定它为整型
> 依赖隐式声明不是一个好主意

#### 3.3 typedef
typedef 为数据类型定义新名字
~~~
char *ptr_to_char; 是一个指向字符的指针
在添加关键字typedef后
typedef char* ptr_to_char;
这个声明把标识符ptr_to_char 作为指向字符的指针类型的新名字
ptr_to_char a; 声明a是一个指向字符的指针
~~~
- 在定义函数指针或指向数组的指针时使用typedef更为合适。


#### 3.4 常量
对于普通的数据类型来说
`int const a; 和 const int a;`没有什么区别，因为对于整型只有值会变成常量

但是对于指针来说有两种东西可能成为常量：‘**指针变量**’和‘**指针所指向的实体**’
~~~
int *pi; 是一个普通的指向整型的指针
而
int const *pci;
则是一个指向整型常量的指针，可以修改指针的值但不能修改它所指向的值
相比之下
int *const pci; 
则是一个指向整型的常量指针。此时指针是常量，它的值无法修改，但是可以修改它所指向的整型的值。
~~~

-----

在 C 语言中，“指向整型的常量指针”和“指向常量整型的指针”是两个非常常见的概念，它们在语法和使用上有所不同。下面我会分别讲解这两者的含义：

1. 指向整型的常量指针（const int* ptr 或 int const* ptr）
这种指针类型表示 指针本身是常量，即指针的值（即它指向的地址）不可修改，但是指针指向的 整型数据 是可以修改的。
~~~
int a = 10;
int b = 20;
const int *ptr = &a; // 或者int const *ptr = &a;
*ptr = 15; // OK，指向的值可以修改
ptr = &b; // 错误，不能修改指针的地址(指针本身是常量)
~~~

2. 指向常量整型的指针（int* const ptr）
这种指针类型表示 指针指向的数据是常量，即指针指向的 整型数据不可修改，但是指针本身可以修改，使其指向不同的地址。
~~~
int a = 10;
int b = 20;
int* const ptr = &a;
*ptr = 15; // 错误，不能修改指向的数据
ptr = &b; // 正确，指针本身可以修改
~~~

3. 两者结合使用（const int* const ptr 或 int const* const ptr）
如果同时声明指针是常量且指向的数据是常量，那么就变成了“常量指针指向常量数据”。
~~~
int a = 10;
const int* const ptr = &a;

*ptr = 15;  // 错误！不能修改指向的数据
ptr = &b;   // 错误！不能修改指针本身
~~~

#### 3.5 作用域(scope)
#### 3.5.1 代码块作用域
特殊情况类似内层代码和外层代码拥有同一个标识符名字内层的标识符会隐藏外层的标识符
> 应该避免在嵌套的代码块中出现相同的变量名

#### 3.6 链接属性
链接属性一共有三种：**external(外部)、internal(内部)和none(无)**

1. 外部链接（External Linkage）
具有外部链接的符号可以在整个程序的多个翻译单元中访问。它意味着符号可以在一个文件中声明，并在其他文件中定义或使用。

全局变量：如果在一个文件中声明了全局变量，并在其他文件中引用该变量，它会具有外部链接。

外部函数：同样地，外部函数可以在一个文件中定义，并在其他文件中调用。

示例：

~~~
// file1.c 
#include <stdio.h>

int global_var = 10; // 外部链接
void func()
{
    printf("Hello World!\n");
}

// file2.c 
extern int global_var; //声明具有外部链接的变量
extern void func(); // 声明外部函数

int main()
{
    func();
    printf("Global variable: %d\n",global_var);
    return 0;
}
~~~
- `global_var`和`func()`都具有外部链接，可以在file2.c中访问

2. 内部链接（Internal Linkage）
具有内部链接的符号只能在同一翻译单元（即同一源文件及其包含的头文件）中访问。它们不能跨文件使用。

static 关键字：使用 static 关键字声明的变量或函数具有内部链接。它意味着该符号的作用域仅限于当前源文件。

示例：

~~~
// file1.c 
#include <stdio.h>
static int internal_var = 10; // 内部链接，只能在file1.c中使用
static void internal_func(){
    // 内部链接，只能在file1.c中调用
    printf("This is an internal function\n");
}

int main()
{
    internal_func();
    printf("Internal variable: %d\n",internal_var);
    return 0;
}

// file2.c 
extern void internal_func(); // 无法调用，因为internal_func在file1.c中是静态的
extern int internal_var; // 无法访问，因为internal_var是静态的
~~~
- `internal_var`和`internal_func()`只能在file1.c中使用，其他文件无法访问它们

3. 无链接（No Linkage）
没有链接的符号意味着它们在某个特定范围内是唯一的，通常这些符号仅限于局部作用域。局部变量和函数的参数一般都是无链接的。

局部变量：它们的作用域仅限于函数内部，其他函数无法访问。

示例：
~~~
void func() {
    int local_var = 10;  // 无链接，仅在func内部有效
    printf("Local variable: %d\n", local_var);
}

int main() {
    func();
    // 下面的代码会导致错误，因为local_var在main函数外不可见
    // printf("Local variable in func: %d\n", local_var);
    return 0;
}
~~~
- `local_var`只能在`func()`内部使用，其他地方无法访问

总结：

**外部链接（External Linkage）**：符号可以在多个翻译单元（源文件）之间共享。通过 `extern` 关键字进行声明。

**内部链接（Internal Linkage）**：符号仅在当前源文件内有效，不能跨文件访问。通过 `static` 关键字来定义。

**无链接（No Linkage）**：符号仅在局部作用域内有效，通常用于函数参数和局部变量。

~~~
static int i;
int func()
{
    int j;
    extern int k;
    extern int i; 
}
~~~
- 当`extern`关键字用于源文件中一个标识符的第一次声明时，它指定该标识符具有external链接属性。但是如上面所示在int i一开始声明了static后并不会在func内部修改extern int i为external链接属性

#### 3.7 存储类型
有三个地方可以用于存储变量：普通内存、运行时堆栈、硬件寄存器。
- 凡是在任何代码块之外的声明的变量总是存储于静态内存中，也就是不属于堆栈的内存，这类变量称为静态(static)变量
- 在代码块内部声明的变量的缺省存储类型是自动的(automatic)，也就是说它存储于堆栈中，称为自动(auto)变量
- 对于在代码块内部声明的变量如果给它加上关键字static，可以使它的存储类型从自动变为静态。函数的形参不能声明为静态，因为实参总是在堆栈中传递给函数
- 关键字register可以用于自动变量的声明，声明变量应该存储于机器的硬件寄存器而不是内存

**初始化**
- (P44)自动变量初始化和静态变量初始化存在一个重要的差别。
> 在静态变量初始化中我们可以把可执行程序想要初始化的值放在当程序执行时变量将会使用的位置。

> 自动变量的初始化需要更多的开销,因为当程序链接时还无法判断自动变量的存储位置，事实上函数的局部变量在函数的每次调用时都可能占据不同的位置

>**自动变量的初始化较之赋值语句效率并无提高**，除了声明为`const`的变量之外这两者只有风格之差，并无效率之别。

> 优点是由于初始化在运行时执行因此可以用任何表达式作为初始化值，例如：
~~~
int
func(int a)
{
    int b = a + 2;
}
~~~
> 最后一个后果是除非对自动变量进行显式的初始化，否则当自动变量创建时，它们的值总是垃圾。


#### 3.8 static关键字

当用于函数定义时，或者用于代码块之外的变量声明时，static关键字用于修改标识符的连接属性(从external 改为 internal)，但标识符的存储类型和作用域不受影响。

用于代码块内部的变量声明时static关键字用于修改变量的存储类型，从自动变量改为静态变量，但变量的链接属性和作用域不受影响。

#### 3.10 总结
- 具有external链接属性的实体总是具有静态存储类型
- 如果一个变量声明于代码块内部，在它前面添加extern关键字将使它所引用的是全局变量而不是局部变量。
 