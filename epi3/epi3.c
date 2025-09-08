#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/*
❌ 简短回答：不能直接用 %s 来输出枚举类型的值。
📌 原因：
枚举在 C 语言里本质上就是 int 类型的整数；

%s 是格式化字符串输出的，用于 char*（即字符串）；

如果你用 %s 去打印一个枚举值，会导致未定义行为（UB）：可能打印乱码、崩溃甚至无输出。
*/
void test1()
{
    enum Liquid {OUNCE = 1, CUP = 8, PINT = 16, QUART = 32, GALLON = 128};
    enum Liquid jar;
    jar = QUART;
    printf("%s\n","new man");
    jar = jar + PINT;
    printf("%s\n",jar);

}

void test2()
{
    long i = 1000000;
    short i1 = i;
    double m = 3.1415926712321; // 会有数据溢出导致的输出错误问题且在编译时未发现
    float m1 = m;

    printf("%f\n",m);
}

int main(void)
{
    // test1();
    // test2();
     
    printf("%d\n",100);
    
    return EXIT_SUCCESS;
}