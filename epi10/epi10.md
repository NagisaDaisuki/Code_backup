# 🤖 结构和联合

- C提供了两种类型的*聚合数据类型(aggregate data type)*。**数组**是相同类型的元素的集合，**结构体**是可具有不同类型的元素的集合。

- ***数组***可以通过下标访问，且数据不能相互赋值，只能通过循环逐个赋值。
- ***结构体***通过名字访问，相同类型的结构体变量可以相互赋值。

## 10.1 结构基础知识

- 结构体是一些值的集合，这些值称为它的**成员(member)**，<u>但一个结构体的各个成员可能具有不同的类型。</u>

- <u>结构变量属于标量类型，所以你可以像对待其他标量类型那样执行相同类型的操作。</u>

### 10.1.1 结构声明

在声明结构时，必须列出它包含的所有成员。

~~~shell
struct tag {member-list} variable-list;
~~~

结构声明语法的不同

~~~shell
struct {
  int   a;
  char  b;
  float c;
}x;


struct {
  int   a;
  char  b;
  float c;
} y[20],*z;
~~~

<u>这两个声明被编译器当作两种截然不同的类型，即使它们的成员列表完全相同。</u>

~~~shell
z = &x;
~~~

这条语句是非法的。

- 使用 **标签(tag)** 和 **类型定义别名(typedef)** 来更方便地声明和定义一个结构体变量。

**标签(tag)** 字段允许为成员列表提供一个名字。

~~~shell
struct SIMPLE{
  int   a;
  char  b;
  float c;
};

struct SIMPLE x,y[20],*z;
~~~

这个声明使用标签来创建变量，且现在`x`,`y`,`z`都是同一种类型的结构变量。

**类型定义别名(typedef)** 字段可以创建一个新的类型。

~~~shell
typedef struct {
  int   a;
  char  b;
  float c;
} Simple;

Simple x;
Simple y[20], *z;
~~~

`Simple`现在是一个类型而不是个结构标签。
> 如果你想在多个源文件中使用同一种类型的结构，你应该把标签声明或`typedef`形式的声明放在一个头文件中。当源文件需要这个声明时可以使用`#include`指令把那个头文件包含进来。

### 10.1.2 结构成员

~~~shell
struct COMPLEX{
  float f;
  int a[20];
  long *lp;
  struct SIMPLE s;
  struct SIMPLE sa[10];
  struct SIMPLE *sp;
};
~~~

结构成员可以是标量、数组、指针甚至是其他结构体。

### 10.1.3 结构成员的直接访问

- 结构变量的成员是通过点操作符`.`访问的。
- 点操作符接受两个参数，左操作数就是结构变量的名字，右操作数就是需要访问的成员的名字。这个表达式的结果就是指定的成员。

~~~shell
struct COMPLEX comp;
(comp.s).a; // 类型为struct SIMPLE 
(comp.sa)[4]; // 同上类型的数组
((comp.sa)[4]).c // 取出数组元素
结合性都是从左到右
comp.sa[4].c; equals ((comp.sa)[4]).c;
~~~

### 10.1.4 结构成员的间接访问

- 对于指向结构体的指针要访问其元素应该执行**间接访问操作`->`**。

~~~shell
void func(struct COMPLEX *cp);
// 第一种访问方式
(*cp).f;
// 第二种访问方式
cp->f;
~~~

### 10.1.5 结构的自引用

~~~shell
// 作为结构这种声明是非法的，程序内部会无限包含自身和结构的成员。(永不终止的递归程序)
// 如果我定义了 struct SELF_REF1 b; 那么 sizeof(SELF_REF1) = sizeof(int) + (4+4+4+.....) + sizeof(int)
// 无法计算，无法在内存中分配一个固定大小的空间。

struct SELF_REF1 {
  int   a;
  struct SELF_REF1 b; // 非法，不能这样定义。
  int   c;

};

// 作为指针这个声明是合法的，因为指针的长度在编译器确定结构体长度前就知道了。
// sizeof(SELF_REF2) = sizeof (int) + sizeof(SELF_REF2*) + sizeof(int)
// 可以计算固定大小空间

struct SELF_REF2{
  int   a;
  struct SELF_REF2 *b;
  int   c;
};

~~~

**<u>事实上一个结构内指向自身结构的指针所指向的是同一种类型的不同结构。</u>**
更高级的数据结构如链表和树，都是用这些技巧实现的。每个结构指向链表的下一个元素或树的下一个分支。

~~~shell
// 这个结构体创建失败了，因为SELF_REF3 直到声明的末尾才定义，所以在结构
// 声明的内部时还尚未定义。
typedef struct {
  int   a;
  SELF_REF3 *b;
  int   c;
}SELF_REF3;

// 解决方案是定义一个结构标签来声明b
typedef struct SELF_REF3_TAG {
  int   a;
  struct SELF_REF3_TAG *b;
  int   c;
}SELF_REF3
// 这次正确定义了结构体。
~~~

### 10.1.6 不完整的声明

- 在声明一些相互之间存在依赖的结构时使用不完整声明(incomplete declaration)

~~~shell
struct B;

struct A {
    struct B  *parnter;
      
};
struct B {
    struct A  *partner;
};
~~~

在A的成员列表中需要标签B的不完整声明。一旦A被声明之后，B的成员列表也可以被声明。

### 10.1.7 结构的初始化

- 位于花括号，由逗号分隔。

~~~shell
struct INI_EX {
  int   a;
  short b[10];
  Simple c;

}x = {
  10,
  {1,2,3,4,5},
  {25,'x',1.9},
};
// 另一种初始化
struct INI_EX x1 = {
  10,
  {1,2,3,4,5},
  {25,'x',1.9},
};
~~~

## 10.2 结构、指针和成员

声明和定义一些结构体和结构体变量

~~~shell
typedef struct {
  int   a;
  short b[2];
}Ex2;

typedef struct EX{
  int   a;
  char  b[3];
  Ex2   c;
  struct EX   *d;
}Ex;

// 定义并初始化
Ex x = {10, "Hi", {5,{ -1 , 25 }}, 0};
Ex *px = &x;
~~~

### 10.2.1 访问指针

**step1:** `px`是一个指针变量，`px`的表达式`Ex *px = x;`表示作为左值的`px`旧值将被一个新值取代。
> 考虑表达式`px + 1`。这个表达式并不是一个合法的左值，因为它的值并不存储于任何可标识的内存位置。`px`的右值更有意思，如果px指向一个结构数组的元素，这个表达式将指向该数组的下一个结构。就算如此`px + 1`仍是非法的，因为我们没办法分辨内存下一个位置所存储的是这些结构元素之一还是其他东西。编译器无法检测到这类错误。

### 10.2.2 访问结构

**step2:** `*px`的右值是px所指向的整个结构。可以用于同类型结构体赋值，作为点操作符的左操作数，访问一个指定的成员，作为参数传递给函数，作为函数的返回值返回。`px`的左值是从`x`接收来的新值，它将接受它的所有成员的新值。

- 作为左值，重要的是位置，而不是这个位置所保存的值。

表达式`*px + 1`是非法的，因为`*px`的结果是一个结构。C语言并没有定义结构体和整型值之间的加法运算。但表达式`*(px+1)`中的`px+1`表示结构体指针但x是一个标量所以这个表达式也是非法的。

### 10.2.3 访问结构成员

**step3:** 表达式`px->a`右值是`10`,`x.a`和`px->a`值相同。

<u>`*px`和`px->a`之间的关系</u>。在这两个表达式中`px`所保存的地址都用于寻找这个结构。但结构体的第一个成员是`a`。所以`a`的地址和结构的地址是一样的。<u>这样`px`看上去是指向整个结构，同时指向结构的第一个成员。</u>但是他们的类型不同，变量`px`被声明为一个指向结构的指针，所以表达式`*px`的结果是整个结构而不是它的第一个成员。

~~~shell
int *pi;

pi = px;
// 这个操作是非法的，因为它们的类型不匹配。
pi = (int *)px;
// 使用强制类型转换就能奏效

// 但是这种方法很危险，因为它避开了编译器的类型检查。
// 正确的表达式更为简单
pi = &px->a;
// -> 操作符的优先级高于&操作符的优先级，所以这个表达式无需使用括号。

~~~

`px->b`的值是一个指针常量，因为`b`是一个数组这个表达式`px->b`不是一个合法的左值。

~~~shell
char *pc;
pc = px->b; // 一个指针常量
pc = px->b[1]; // 指向数组的第二个元素
~~~

### 10.2.4 访问嵌套的结构

**step4:** 表达式`px->c`也是指向一个结构体，它的左值是整个结构。

~~~shell
int num = px->c.a; 指向结构体内结构体并访问结构体成员a
short *num1 = px->c.b;
int num2 = *px->c.b;
~~~

### 10.2.5 访问指针成员

**step5:** `px->d`的右值是0，左值是本身的内存位置。`*px->d`是非法的操作，因为d内包含了一个NULL指针，所以它不指向任何东西。

~~~shell
Ex te;
te = *px->d;
x.d = &te;
~~~

> **空指针的本质：地址0**
>> 空指针是一个特殊的指针值，它表示该指针不指向任何有效的内存对象。
>> *解引用空指针后CPU会尝试访问地址0*-->*操作系统会捕获异常*-->*触发硬件异常(Page Fault)或(Segmentation Fault)*-->*内核终止程序*。

## 10.3 结构的存储分配

- 编译器按照成员列表的顺序一个接一个地给每个成员分配内存。<u>只有当存储成员时需要满足正确的边界要求时，成员之间才可能出现用于填充的额外内存空间。</u>

~~~shell
struct ALIGN{
  char  a;
  int   b; 
  char  c;
};
~~~

这个结构体实际分配了12个字节的内存空间但是有6个字节空间实际上不能访问。

~~~shell
struct ALIGN2{
  int b;
  char a;
  char c;

};
~~~

这个结构体实际分配了8个字节的内存空间。（两个字符可以紧挨着存储，最后有2个字节被浪费）
> 但是实际上依程序的可维护性和可读性而言不是特别大的内存损失都不需要重新排。

- 在程序创建成百上千个结构体时内存浪费问题就更为明显。
- 可以使用`offsetof`宏（定义于`stddef.h`）判断结构体内成员距离首地址的偏移值

~~~shell
offsetof(type,member) // type 是结构体类型名，member是结构体里面的成员名
offsetof(struct ALIGN, b) // 返回值是 4,也就是成员a占用了4个字节用于结构体内内存对齐
~~~

## 10.4 作为函数参数的结构

- 非必要不建议将结构体作为函数参数传递
- 结构体作为一个标量的大小可能会比想象中的大

~~~shell
typedef struct
{
  char    product[PRODUCT_SIZE];
  int     quantity;
  float   unit_price;
  float   total_amount;
};

void print_receipt(Transaction trans);
void print_receipt(Transaction *trans);
~~~

一个传递的是结构体的拷贝，一个传递的是结构体指针。就大小而言指针比结构体小得多，效率更高。

~~~shell
Transaction print_receipt(Transaction trans);
void print_receipt(Transaction *trans);
~~~

如果结构体作为函数返回值在堆栈上的操作效率会更低，传递结构体指针可以直接在函数内部完成结构体成员的修改。

## 10.5 位段

- 结构体具有实现 **位段(bit field)** 的能力
- 位段的成员是一个或多个位的字段，这些不同长度的字段实际上存储于一个或多个整型变量中。
- 位段成员必须声明为`int`,`unsigned int`,`signed int`, `_Bool(C99)`类型，在成员名的后面是一个冒号和一个整数。
- 不能对位段成员取地址(不能使用`&`运算符)
- 位段不能是数组
- 可移植性的程序应该避免使用位段。
- 位段和结构体成员一样之间需要内存对齐(在位段与位段之间插入填充位(Padding))

~~~shell
struct CHAR {
  unsigned  ch  : 7;
  unsigned font : 6;
  unsigned size : 19;
};
~~~

因为最后一个位段`size`过于庞大(大于短整型的长度)，所以可以利用前两个位段`ch`和`font`所剩余的位来增加`size`的位数，这样就避免了声明一个32位的整数来存储`size`位段。
> CHAR这个结构体内的位段说明了位段可以把长度为奇数的数据包装在一起，节省存储空间

## 10.6 联合

- 联合所有成员引用的是**内存中的相同位置**
- 适用于在不同时刻把不同的东西存储于同一个位置时

~~~shell
union {
  float f;
  int   i;
} fi;

fi.f = 3.14159;
printf("%d\n", fi.i);
~~~

在一个浮点型和整型都是32位的机器上，变量 `fi` 只占据内存中的一个32位的字。最后用占位符`%d`输出一个浮点数不是`3`而是`1078530000`，与IEEE754单精度浮点标准有关。

### 10.6.1 变体记录

- 内存中某个特定的区域将在不同的时刻存储不同类型的值

在 C 语言中，可以使用 **联合体（Union）** 和 **结构体（Struct）** 结合的方式来模拟 `Pascal` 语言中的**变体记录（Variant Record）**，也称为**带标签的联合体（Tagged Union）**。

这种模式是 C 语言处理异构数据集合的标准方法，同时提供了类型安全性和可预测性。

#### 一个存货系统的变体记录

~~~shell
// 前两个结构指定每个零件和装配件必须存储的内容
struct PARTINFO {
  int     cost;
  int     supplier;
};

struct SUBASSYINFO {
  int     n_parts;
  struct {
    char partno[10];
    short quan;
  }part[MAXPARTS];
};

// 存货记录包含每个项目的一般信息并包含了一个联合
struct INVREC {
  char    partno[10];
  int     quan;
  enum    { PART, SUBPASSY }    type;
  union   {
          struct PARTINFO       part;
          struct SUBASSYIINFO   subassy;
  }info;
};

// 操作名为 rec 的 INVERC 结构变量
if (rec.type == PART){
  y = rec.info.part.cost;
  z = rec.info.part.supplier;
}
else{
  y = rec.info.subpassy.nparts;
  z = rec.info.subpassy.parts[0].quan;
}
~~~

### 10.6.2 联合的初始化

- 联合初始化的初始值必须是联合第一个成员的类型，且必须位于一对花括号里

~~~shell
union {
  int   a;
  float b;
  char  c[4];
} x = { 5 };
~~~

> 把`x.a`初始化为 5,如果给出的初始值是任何其他类型都会被转换为一个整数并赋值给`x.a`
