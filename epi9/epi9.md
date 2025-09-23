# 💝 字符串、字符和字节

- 字符串是一种重要的数据类型，但是C语言并没有显式的字符串数据类型，因为字符串以字符串常量的形式出现或者存储于字符数组中。
- 操作字符串变量时必须额外小心各种可能导致缓冲区溢出的操作。

## 9.1 字符串基础

- 字符串是一串**零个或多个字符**，并且以一个**位模式为全0的NUL字符结尾**。

> 字符串所包含的字符内部不能出现NUL字节
>
## 9.2 字符串长度

- 字符串的长度就是它所包含的字符个数。

使用标准库头文件`#include <string.h>`中的函数计算字符串长度

~~~shell
strlen 原型
size_t strlen (char const *string);
~~~

> size_t 是一个无符号整数类型，且这个类型是在头文件`stddef.h`中定义的

- 无符号数的使用需要考虑是否会产生负数

~~~shell
if (strlen(x) >= strlen(y)) ...
if (strlen(x) - strlen(y) >= 0) ...
~~~

这两个式子是不相等的，第二行的`strlen(x) - strlen(y)`的返回结果是一个无符号数，**无符号数绝不可能是负数**！

**strlen原型**

~~~shell
#include <stddef.h>

size_t 
strlen(char const *string)
{
  int length;
  
  for (length = 0; *string++ != '\0';)
    length += 1;
  return length;
}
~~~

- 表达式中如果同时存在无符号数和有符号数，可能会产生奇怪的结果

~~~shell
if (strlen(x) >= 10) ...
if (strlen(x) - 10 >= 0) ...
~~~

这两个式子也是不相等的，原因和上面相同。
> 如果把strlen的返回值强制转换为`int`，就可以消除这个问题。

**tips:**
> 自己重写一个标准库函数可能会比标准库函数效率更高，如果合理使用寄存器register声明和一些技巧，**但事实上很少能如愿**。
>> <u>寻找一种更好的算法比改良一种差劲的算法更有效率，复用已经存在的软件比重新开发一个效率更高。</u>

## 9.3 不受限制的字符串函数

- 最常用的字符串函数都是**不受限制**的，就是说它们只是通过寻找字符串参数结尾的`NUL`字节来判断它的长度。

### 9.3.1 复制字符串

~~~shell
char *strcpy(char *dst, char const *src);
~~~

这个函数把参数src字符串复制到dst参数，<u>由于dst参数将进行修改，所以它必须是个字符数组或者是一个指向动态分配内存的数组的指针，**不能使用字符串常量**</u>

> <u>程序员必须保证目标字符数组的空间足以容纳需要复制的字符串。</u>因为如果字符串比数组长，多余的字符仍然被复制，它们将覆盖原先存储于数组后面的内存空间的值。
>> strcpy无法解决这个问题，因为它无法判断目标字符数组的长度。

### 9.3.2 连接字符串

~~~shell
char *strcat( char *dst, char const *src);
~~~

- 找到字符串末尾NUL并将src中的首字符覆盖掉NUL  

常见`strcat`用法

~~~shell
strcpy( message, "Hello ");
strcat( message, customer_name );
strcpy( message, ", how are you?");
~~~

### 9.3.3 函数的返回值

- `strcpy`和`strcat`都返回它第一个参数的一份拷贝

将函数返回值作为另一个函数的参数

~~~shell
strcat(strcpy(dst,a),b);
~~~

> 首先执行`strcpy`将字符串从a复制到dst并返回dst。然后这个返回值成为`strcat`函数的第一个参数，`strcat`函数把b添加到dst的后面。

但是在可读性上其实不如

~~~shell
strcpy(dst,a);
strcat(dst,b);
~~~

- 事实上，在这些函数的绝大多数调用中它们的返回值只是被简单地忽略。

### 9.3.4 字符串比较

- 比较两个字符串涉及对两个字符串对应的字符逐个进行比较，直到发现不匹配为止。
- 那个最先不匹配的字符中较"小"(字符集中序数较小)的那个字符所在的字符串被认为"小于"另外一个字符串

~~~shell
int strcmp(char const *s1, char const *s2);
~~~

如果`s1`小于`s2`，strcmp函数返回一个小于零的值，反之返回一个大于零的值。相等返回零。

~~~shell
if (strcmp(a,b)) // 用于布尔值测试是一种坏风格
if (strcmp(a,b) > 0) // 用于与零进行比较更好
else if (strcmp(a,b) < 0)
else
~~~

## 9.4 长度受限的字符串函数

<u>标准库还包含了一些函数，它们以一种不同的方式处理字符串。</u>

~~~shell
char *strncpy(char *dst, char const *src, size_t len);
char *strncat(char *dst, char const *src, size_t len);
char *strncmp(char const *s1, char const *s2, size_t len);
~~~

这些函数接受一个显式的长度参数，用于**限定**进行复制或比较的字符数。

- 注意⚠️：如果strlen(src)的值大于或等于len，<u>那么只有len个字符被复制到dst中。它的结果将不会以**NUL**字节结尾。</u>

> strncpy 调用的结果可能不是一个字符串，因此字符串必须以NUL字节结尾。

保证strncpy的结果是以'\0'结尾的

~~~shell
char buffer[BSIZE];
...
strncpy(buffer, name, BSIZE);
buffer[BSIZE - 1] = '\0';
~~~

如果name的内容可以容纳于buffer中最后的赋值语句无效。

如果strlen(name) >= BSIZE 那么最后一条赋值语句可以截断name的字符防止缓存区溢出。

> strncat总是在结果字符串后面添加一个NUL字节，所以不会有这种问题；strncmp只比较len长度的字符串是否相等，如果strlen(name)比BSIZE大则只比较BSIZE长度个字符。

## 9.5 字符串查找基础

### 9.5.1 查找一个字符

~~~shell
char *strchr(char const *str, int ch);
char *strrchr(char const *str, int ch);
~~~

> 虽然ch是`int`类型但是包含一个字符值。

- `strchr`在字符串str中查找字符ch第一次出现的位置，找到后函数返回一个指向该位置的指针，如果该字符不存在则返回NULL指针。strrchr返回一个指向字符串中最后一次出现的位置。

~~~shell
char string[20] = "Hello there, honey.";
char *ans;
ans = strchr(string, 'h');
~~~

### 9.5.2 查找任何几个字符

~~~shell
char *strpbrk(char const *str, char const *group);
~~~

- 返回一个指向str中第一个匹配group中任何一个字符的字符位置。如果未找到匹配则返回NULL指针。区分大小写。

~~~shell
char string[20] = "Hello there, honey.";
char *ans;
ans = strchr(string, "aeiou");
~~~

ans所指向的位置是string + 1，因为这个位置是第二个参数中的字符第一次出现的位置。区分大小写。

### 9.5.3 查找一个子串

~~~shell
char *strstr(char const *s1, char const *s2);
~~~

- 在s1中查找s2第一次出现的位置，并返回一个指向该位置的指针；如果s2并没有完出现在s1返回一个NULL指针；如果第二个参数是一个空指针函数返回s1。

#### 自己实现一个 `strtstr` 和 `strrpbrk` 函数

~~~shell
#include <string.h>

char*
my_strrstr(char const *s1, char const *s2)
{
  register char *last;
  register char *current;

  // 把指针初始化为我们已经找到的前一次匹配
  last = NULL;
  
  // 只在第二个字符串不为空的时候进行查找，如果s2为空返回NULL
  
  if (*s2 != '\0')
  {
    // 查找 s2 在 s1 中第一次出现的位置。
    current = strstr(s1,s2);
    while (current != NULL)
    {
      last = current;
      current = strstr(last + 1, s2);
    }
  }
  return last; // 返回指向我们找到的最后一次匹配的起始位置的指针。
}
~~~

~~~shell
#include <string.h>

char *
my_strrpbrk(char const *str, char const *group)
{
  register char *last;
  register char current;
  
  // 把指针初始化为我们已经找到的前一次匹配
  last = NULL;
  
  if (*s2 != '\0')
  {
    current = strpbrk(str, group);
    while (current != NULL)
    {
      last = current;
      current = strpbrk(last + 1, group);
    }
  }
  return last;
}
~~~

## 9.6 高级字符串查找

### 9.6.1 查找一个字符串前缀

- `strspn`和`strcspn`函数用于计算字符串开头连续匹配指定字符集中的字符的个数

~~~shell
size_t strspn(char const *str, char const *group);
size_t strcspn(char const *str, char const *group);
~~~

`str`: 要检查的字符串。  
`group`：包含要匹配的字符集的字符串。

>`strspn` 从 `str1` 的第一个字符开始，依次检查每个字符。只要这个字符在 `str2` 中能找到，就继续向后检查。**一旦遇到一个不在 `str2` 中的字符，函数就停止并返回已匹配的字符数。**

> `strcspn` 从 `str1` 的第一个字符开始，依次检查每个字符。只要这个字符不在 `str2` 中，就继续向后检查。一旦遇到一个在 `str2` 中的字符，函数就停止并返回已检查的字符数。

~~~shell
#include <stdio.h>
#include <string.h>

int main() {
    const char *sentence = "Hello, world!";
    const char *charset_vowels = "aeiou";
    const char *charset_alpha = "abcdefghijklmnopqrstuvwxyz";

    size_t length1 = strspn(sentence, "Heo");
    printf("The length of the initial part of \"%s\" consisting of 'H', 'e', 'o' is: %zu\n", sentence, length1); 
    // 输出: 2 (因为 'l' 不在 "Heo" 中)

    size_t length2 = strspn(sentence, charset_alpha);
    printf("The length of the initial part of \"%s\" consisting of letters is: %zu\n", sentence, length2);
    // 输出: 5 (因为 ' ' 不在字母表中)

    return 0;
}
~~~

### 9.6.2 查找标记

- `strtok`函数用于分割字符串。它会根据指定的分隔符，将字符串分解成一系列的标记(token)。

~~~shell
char *strtok(char *str, char const *sep);
~~~

`str`：要被分割的字符串。
`sep`：包含一个或多个分隔符的字符串。

> strtok是在字符串本身进行处理的(in-place)，建议使用原字符串的拷贝进行操作。

- `strtok`的使用非常特殊，因为它是有状态的：
  - 第一次调用：传入要分割的字符串`str`。它会找到第一个分隔符，用`\0`替换它，并返回第一个标记的指针。
  - 后续调用：传入`NULL`作为`str`参数。`strtok`会从上次停止的位置继续，找到下一个分隔符，用`\0`替换它，并返回下一个标记的指针。

~~~shell
#include <stdio.h>
#include <string.h>

int main(void)
{
  char str[] = "apple,banana-orange";
  const char *delimiters = ",-";
  char *token;

  // 第一次调用， 传入字符串
  token = strtok(str,delimiters);
  printf("First token: %s\n", token);
  
  // 后续调用，传入NULL
  while(token != NULL)
  {
    token = strtok(NULL,delimiters);
    if (token != NULL){
      printf("Next token: %s\n",token);
    }
  }
  return 0;
}
~~~

## 9.7 错误信息

- 当你调用一些函数，请求操作系统执行一些功能如打开文件时，如果出现错误，操作系统是通过设置一个外部的整型变量`errno`进行错误代码报告的。`strerror`函数把其中一个错误代码作为参数并返回一个指向用于描述错误的字符串的指针。

~~~shell
char *stderror(int error_number);
~~~

事实上，返回值应该被声明为`const`，因为你不应该修改它。

- `strerror`函数用于将错误编号转换为人类可读的错误信息字符串。

~~~shell
#include <stdio.h>
#include <string.h>
#include <errno.h>
// 必须包含此头文件来使用 errno

int main(void)
{
  FILE *file;
  // 尝试打开一个不存在的文件
  file = fopen("non_existent_file.txt", "r");
  
  // 如果 fopen 失败
  if (file == NULL)
    printf("Error opening file: %s\n", strerror(errno));
  else
  {
    printf("File opened successfully.\n");
    fclose(file);
  }
  return 0;
}
~~~

## 9.8 字符操作

- 字符操作的原型位于`ctype.h`头文件中，分为字符分类函数和字符转换函数

### 9.8.1 字符分类

<h4>字符分类函数</h4>

| 函数 | 如果它的参数符合下列条件就返回真 |
|:---:|:---:|
|isspace|空白字符: '空格', 换页'\f'，换行 '\n', 回车 '\r', 制表符 '\t'或垂直制表符'\v'|
|isdigit|十进制数字0~9|
|isxdigit|十六进制数字，包括所有十进制数字，小写字母a\~f,大写字母A\~F|
|islower|小写字母a~z|
|isupper|大写字母A~Z|
|isalpha|字母a\~z A\~Z|
|isalnum|字母或数字，a\~z,A\~z或0~9|
|ispunct|标点符号，任何不属于数字或字母的图形字符(可打印符号)|
|isgraph|任何图形字符|
|isprint|任何可打印字符，包括图形字符和空白字符|

### 9.8.2 字符转换

~~~shell
int tolower(int ch);
int toupper(int ch);

if (ch >= 'A' && ch <= 'Z') 在ASCII字符集的机器上能够运行，但是其他字符集有可能会失败
if (isupper(ch))
就都能顺利运行
~~~

## 9.9 内存操作

- 根据定义，字符串由一个NUL字节结尾，所以字符串内部不能包含任何NUL字符。但是非字符串数据内部包含零值的情况并不罕见。你无法使用字符串函数来处理这种类型的数据，因为当它们遇到第一个NUL字节时将停止工作。
- 使用**内存操作函数**可以处理任意的字节序列

~~~shell
void *memcpy(void *dst, void const *src, size_t length);
void *memmove(void *dst, void const *src, size_t length);
void *memcmp(void const *a, void const *b, size_t length);
void *memchr(void const *a, int ch, size_t length);
void *memset(void *a, int ch, size_t length);
~~~

- 和字符操作函数类似，对于memcpy()函数，如果src与dst以任何形式出现了重叠，它的结果是未定义的。但是memmove()函数可以重叠。
- 内存操作函数传入的长度为内存长度不是元素长度。
- 任何类型的指针都可以转换为`void*`型指针。

`memcpy`

`memcpy` copies a block of memory from a source to a destination location.

**Parameters:**

- `dest`: A pointer to the destination memory block.
- `src`: A pointer to the source memory block.
- `n`: The number of bytes to copy

**Use case:** Copying data between non_overlapping memory regions.

~~~shell
#include <stdio.h>
#include <string.h>

int main(void)
{
  int source_array[] = {1,2,3,4,5};
  int destinaion_array[5];
  
  // copy 5 integers from soure_array to destination_array
  memcpy(destination_array, source_array, sizeof(source_array));

  printf("Destinaion array: ");
  for (int i = 0; i < 5; i++)
  {
    printf("%d ",destination_array[i]);
  }
  printf("\n");
  return 0;
}
~~~

`memmove`

`memmove` copies a block of memory from a source location to a destination location, even if the memory blocks overlap.

**Parameters:** Same as `memcpy`

**Use case:** Shifting data within the same array or buffer. This is safer than `memcpy` for overlapping regions.

~~~shell
#include <stdio.h>
#include <string.h>

int main(void)
{
  char str[] = "abcdefgh";
  
  // Shift the string two characters to the left
  // The source and destination overlap (str + 2 and str)
  memmove(str, str + 2,strlen(str) - 2);
  
  // manually add the null terminator since memmove doesn't
  str[strlen(str) - 2] = '\0';
  printf("String after memmove: %s\n", str); // prints "cdefgh"

  return 0;

}
~~~

`memchr`

`memchr` search a block of memory for the first occurrence of a specific byte.

**Parameters:**

- `a`: A pointer to the memory block to search
- `ch`: The byte value to search for. It's passed as an `int` but is treated as an `unsigned char`.
- `length`: The number of bytes to search.

**Return Value:**

- A pointer to the first occurrence of the byte `ch` within the first `n` bytes of the memory block `a`.
- A null pointer (`NULL`) if the byte is not found.

**Use Case:** Searching for a specific byte within a block of raw binary data.Unlike string functions like `strchr`. `memchr` continues its search past null terminators (`\0`).

~~~shell
#include <stdio.h>
#include <string.h>

int main(void) {
  // This array contains a null byte in the middle.
  char data[] = {'h', 'e', 'l', 'l', 'o', '\0', 'w', 'o', 'r', 'l', 'd'};
  char *result;
- 
  // Search for the character 'o' within the first 11 bytes of the array.
  // A string search function like strchr would stop at the '\0'
  result = memchr(data, 'o', sizeof(data));
  if (result != NULL) {
    printf("Found 'o' at memory address: %p\n", result);
    printf("Character found: '%c'\n", *result);

    // Calculate the index of the found character
    size_t index = (size_t)(result - data);
    printf("It is located at index: %zu\n", index);
  } else {
    printf("The character was not found.\n");
  }
  return 0;
}
~~~

`memcmp`

`memcmp` compares a specified number of bytes in two memory blocks

**Parameter:**

- `a`: A pointer to the first memory block
- `b`: A pointer to the second memory block
- `length`: The number of bytes to compare.

**Use case:** Comparing raw binary data, which may contain null bytes that would terminate string functions like `strcmp`.

~~~shell
#include <stdio.h>
#include <string.h>

int main(void)
{
  char data1[] = "Hello";
  char data2[] = "HellO";
  char data3[] = "Hello";
  
  // compare the first 5 bytes of data1 and data2
  int result1 = memcmp(data1, data2, 5);
  if (result1 != 0)
  {
    printf("data1 and data2 are different.\n");
  }
  // compare the first 5 bytes of data1 and data2
  
  int result2 = memcmp(data1, data3, 5);
  if(result2 != 0)
  {
    printf("data1 and data3 are different.\n");
  }
  return 0;
}
~~~

`memset`

`memset` fills a block of memory with a specified byte value.

**Parameters:**

- `a`: A pointer to the memory block to fill.
- `ch`: The value to be set. It's passed as an `int` but is converted to an `unsigned char`.
- `length`: The number of bytes to fill.

**Use case:** Initializing a block of memory, such as an array or a structure, to all zeros or a specific value.

~~~shell
#include <stdio.h>
#include <string.h>

int main(void)
{
  char buffer[10];
  
  // Initialize all 10 bytes of the buffer to 'A'
  memset(buffer, 'A', sizeof(buffer));
  printf("Buffer after memset: %.10s\n",buffer);
  
  // Initialize the buffer to all zeros (a common and safe practice)
  memset(buffer, 0, sizeof(buffer));
  printf("Buffer after zeroing: %d\n", buffer[0]); // Prints 0

  return 0;
}
~~~

## 9.10 总结

- 字符串就是零个或多个字符的序列，该序列以一个NUL字节结尾。

## 9.13 问题

1. C语言缺少显式字符串数据类型，这是一个优点还是一个缺点？

Answer:

C语言缺少显式的字符串数据类型，既是它的**优点**，也是它的**缺点**。  

优点：灵活性和高效性

C语言的字符串被实现为以 **空字符（\0）** 结尾的字符数组，这带来了以下几个显著的优点：

- 内存效率高：C语言的字符串存储非常紧凑，没有额外的元数据（如长度信息）。这使得C语言程序在处理大量文本时，内存开销极小。

- 直接操作内存：字符串作为数组，可以像普通数组一样通过指针直接访问和操作每个字符。这给予了程序员极大的灵活性，可以实现各种高效的算法，例如原地修改、零拷贝（zero-copy）等。这在系统编程、嵌入式开发和性能关键的应用中至关重要。

- 互操作性强：几乎所有编程语言都支持字节数组或指针，这使得C语言的字符串可以轻松地与其他语言（如Python、Rust、Java等）进行接口交互，而无需复杂的类型转换。

缺点：安全性和易用性

这种设计也带来了明显的缺点，尤其是在安全和易用方面：

- 安全性风险：由于字符串的长度信息不是显式存储的，字符串处理函数（如 strcpy、strcat、sprintf）都假定目标缓冲区足够大，这极易导致缓冲区溢出。这是C语言长期以来面临的最大安全挑战之一。程序员必须手动跟踪字符串长度，否则会引发严重的漏洞。

- 容易出错：忘记在字符串末尾添加 \0，或不小心覆盖了它，都会导致程序读取到无效内存，引发未定义行为。初学者经常会因为这些问题而感到困惑。

- 操作不便：字符串的拼接、截取等操作不像高级语言那样简洁。例如，要拼接两个字符串，你需要手动计算所需空间、分配内存、然后使用 strcpy 和 strcat，整个过程繁琐且容易出错。
